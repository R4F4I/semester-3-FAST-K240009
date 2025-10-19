""" 


**Concept:** This is the most advanced problem, combining OOP, API interaction, and multi-threading. You will build a simulated real-time dashboard that fetches data from multiple sources concurrently.

**Description:**

You are building a command-line "dashboard" for a financial company. The dashboard needs to display up-to-the-minute information from three different (mock) APIs: one for stock prices, one for market news, and one for currency exchange rates. Since fetching data from APIs can be slow, you must use multi-threading to fetch the data concurrently to keep the dashboard responsive.

**The Mock APIs (to be built with Flask):**

-   **`GET /stocks/<ticker>`**: Returns the price for a stock `ticker`. To simulate network latency, add a `time.sleep(1)` before returning the response.
    
    -   Response: `{"ticker": "GOOGL", "price": 145.50}`
        
-   **`GET /news`**: Returns the latest market news `headline`. Add a `time.sleep(2)` to simulate a slower API.
    
    -   Response: `{"headline": "Tech stocks rally on positive inflation report."}`
        
-   **`GET /exchange_rate/<base>/<target>`**: Returns the exchange `rate` between two currencies. Add a `time.sleep(1.5)`.
    
    -   Response: `{"base": "USD", "target": "EUR", "rate": 0.92}`
        

**Core Classes:**

1.  **`APIDataFetcher` Class:**
    
    -   **Attributes:** `api_url`.
    -   **Method:** `fetch()`: This method will make the API request and return the JSON data. This is the method you will run in a separate `thread`.
        
2.  **`Dashboard` Class:**
    
    -   **Attributes:** `stock_tickers` (list of `tickers` to watch), `currency_pairs` (list of pairs like `('USD', 'EUR')`).
    -   **Methods:**
        
        -   `fetch_all_data()`: This is the central logic.
            
            1.  It should create a list of `APIDataFetcher` instances for each `stock`, the `news` endpoint, and each `currency_pair`.
            2.  It should then create and start a new `thread` for each `APIDataFetcher`'s `fetch()` method.
            3.  It must wait for all `threads` to complete (using `thread.join()`).
            4.  As data comes back from each `thread`, it should be stored appropriately.
                
        -   `display()`: This method should format and print the fetched data in a clean, dashboard-like format in the console.
            

**Challenge:**

1.  Build the three mock API endpoints using `Flask`, including the simulated delays.
2.  Implement the `APIDataFetcher` and `Dashboard` classes.
3.  Your main script should create a `Dashboard` instance with a list of at least 3 `stocks` and 2 `currency_pairs`.
4.  The script should then enter a loop that, every 10 seconds:
    
    -   Calls `fetch_all_data()` to get the latest data concurrently.
    -   Calls `display()` to refresh the dashboard in the console.
        
5.  Ensure that your threading implementation is safe and correctly retrieves all the data before the `display` method is called.

"""

import requests
import threading
import time
import os
import random
from flask import Flask, jsonify

# --- Configuration ---
API_PORT = 5000
API_HOST = "127.0.0.1" # localhost
API_BASE_URL = f"http://{API_HOST}:{API_PORT}"

WATCH_STOCKS = ["GOOGL", "MSFT", "AAPL"]
WATCH_CURRENCIES = [("USD", "EUR"), ("GBP", "USD")]
UPDATE_INTERVAL_SECONDS = 10

# --- Flask Mock API Setup ---
app = Flask(__name__)

# Mock data (global to be accessible by Flask routes and updated by stock API)
mock_stocks_data = {
    "GOOGL": {"ticker": "GOOGL", "price": 145.50},
    "MSFT": {"ticker": "MSFT", "price": 330.10},
    "AAPL": {"ticker": "AAPL", "price": 180.25},
    "AMZN": {"ticker": "AMZN", "price": 135.70},
    "NVDA": {"ticker": "NVDA", "price": 470.00},
}

mock_news_headlines = [
    "Tech stocks rally on positive inflation report.",
    "Central bank hints at interest rate cuts.",
    "Global trade tensions ease, market reacts positively.",
    "Energy sector experiences unexpected surge.",
    "New tech startup disrupts established industry."
]

mock_exchange_rates = {
    ("USD", "EUR"): 0.92,
    ("EUR", "USD"): 1.08,
    ("USD", "GBP"): 0.79,
    ("GBP", "USD"): 1.27,
}

@app.route('/stocks/<ticker>', methods=['GET'])
def get_stock_price(ticker):
    time.sleep(1) # Simulate network latency
    current_price = mock_stocks_data.get(ticker.upper(), {}).get("price")
    if current_price:
        change = random.uniform(-5, 5) # price change between -5 and +5
        new_price = round(current_price + change, 2)
        mock_stocks_data[ticker.upper()]["price"] = new_price # Update mock data
        return jsonify({"ticker": ticker.upper(), "price": new_price})
    return jsonify({"error": "Stock not found"}), 404

@app.route('/news', methods=['GET'])
def get_news():
    time.sleep(2) # Simulate slower API
    headline = random.choice(mock_news_headlines) # Get a random headline
    return jsonify({"headline": headline})

@app.route('/exchange_rate/<base>/<target>', methods=['GET'])
def get_exchange_rate(base, target):
    time.sleep(1.5) # Simulate latency
    rate = mock_exchange_rates.get((base.upper(), target.upper()))
    if rate is not None:
        # Simulate slight fluctuation for exchange rates
        change = random.uniform(-0.01, 0.01)
        new_rate = round(rate + change, 4)
        return jsonify({"base": base.upper(), "target": target.upper(), "rate": new_rate})
    return jsonify({"error": "Exchange rate not available"}), 404

# Function to run Flask app in a separate thread
def run_flask_app():
    print(f"Flask Mock API starting on {API_BASE_URL}...")
    # debug=False is crucial when running Flask in a separate thread,
    # otherwise it might try to restart the server multiple times.
    app.run(host=API_HOST, port=API_PORT, debug=False, use_reloader=False)

# --- Dashboard Client Classes ---
class APIDataFetcher:
    def __init__(self, endpoint, params=None):
        self.url = f"{API_BASE_URL}/{endpoint}"
        self.params = params
        self.data = None
        self.error = None

    def fetch(self):
        try:
            response = requests.get(self.url, params=self.params)
            response.raise_for_status()
            self.data = response.json()
        except requests.exceptions.RequestException as e:
            self.error = str(e)
            self.data = {"error": self.error}

class Dashboard:
    def __init__(self, stock_tickers, currency_pairs):
        self.stock_tickers = stock_tickers
        self.currency_pairs = currency_pairs
        self.current_data = {
            "stocks": {},
            "news": None,
            "exchange_rates": {}
        }
        self.lock = threading.Lock()

    def fetch_all_data(self):
        fetchers = []
        threads = []

        for ticker in self.stock_tickers:
            fetcher = APIDataFetcher(f"stocks/{ticker}")
            fetchers.append(fetcher)

        news_fetcher = APIDataFetcher("news")
        fetchers.append(news_fetcher)

        for base, target in self.currency_pairs:
            fetcher = APIDataFetcher(f"exchange_rate/{base}/{target}")
            fetchers.append(fetcher)

        for fetcher in fetchers:
            thread = threading.Thread(target=fetcher.fetch)
            threads.append(thread)
            thread.start()

        for thread in threads:
            thread.join()

        with self.lock:
            self.current_data = {
                "stocks": {},
                "news": None,
                "exchange_rates": {}
            }
            for fetcher in fetchers:
                if fetcher.data:
                    if "ticker" in fetcher.data:
                        self.current_data["stocks"][fetcher.data["ticker"]] = fetcher.data["price"]
                    elif "headline" in fetcher.data:
                        self.current_data["news"] = fetcher.data["headline"]
                    elif "base" in fetcher.data and "target" in fetcher.data:
                        pair = f"{fetcher.data['base']}/{fetcher.data['target']}"
                        self.current_data["exchange_rates"][pair] = fetcher.data["rate"]

    def display(self):
        os.system('cls' if os.name == 'nt' else 'clear')

        print("--- Real-time Market Dashboard ---")
        print(f"Last Updated: {time.strftime('%Y-%m-%d %H:%M:%S')}\n")

        print("### Stock Prices ###")
        with self.lock:
            if self.current_data["stocks"]:
                for ticker, price in self.current_data["stocks"].items():
                    print(f"  {ticker}: ${price:.2f}")
            else:
                print("  No stock data available.")

            print("\n### Latest News ###")
            if self.current_data["news"]:
                print(f"  - {self.current_data['news']}")
            else:
                print("  No news available.")

            print("\n### Exchange Rates ###")
            if self.current_data["exchange_rates"]:
                for pair, rate in self.current_data["exchange_rates"].items():
                    print(f"  {pair}: {rate:.4f}")
            else:
                print("  No exchange rate data available.")
        print("\n----------------------------------")

# --- Main Execution ---
if __name__ == "__main__":
    # Start the Flask API in a separate thread
    flask_thread = threading.Thread(target=run_flask_app)
    flask_thread.daemon = True # Allow the main program to exit even if this thread is still running
    flask_thread.start()

    # Give the Flask app a moment to spin up before the client tries to connect
    time.sleep(2)

    dashboard = Dashboard(WATCH_STOCKS, WATCH_CURRENCIES)

    print("Starting Dashboard. Press Ctrl+C to stop.")
    try:
        while True:
            dashboard.fetch_all_data()
            dashboard.display()
            time.sleep(UPDATE_INTERVAL_SECONDS)
    except KeyboardInterrupt:
        print("\nDashboard stopped.")
    except requests.exceptions.ConnectionError:
        print("\nError: Could not connect to the Flask API. Ensure it started correctly.")