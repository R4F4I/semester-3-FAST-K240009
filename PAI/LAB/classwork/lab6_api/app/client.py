# --------------------------------------------------------------------------
# File: api_client.py
# Description: A Python application that consumes the local Flask API,
# fetches product and order data, and displays it in the console.
# --------------------------------------------------------------------------
import requests
import json
import time

# The base URL of the Flask API
BASE_URL = "http://127.0.0.1:5000/api"

# --- Common Fetching Logic ---

def safe_api_call(endpoint, item_key, display_formatter):
    """
    Handles API request, error checking, and display for a given endpoint.
    This centralized function makes it easy to add new endpoints.
    
    Args:
        endpoint (str): The API path part (e.g., 'products', 'orders').
        item_key (str): The key in the JSON response containing the list of items.
        display_formatter (function): A function to format and print the fetched items.
    """
    url = f"{BASE_URL}/{endpoint}"
    print(f"\n--- Fetching Data from: {url} ---")
    time.sleep(0.5)

    try:
        # 1. Make the GET request to the API
        response = requests.get(url, timeout=5)

        # 2. Check for successful response (HTTP status code 200)
        response.raise_for_status() # Raises an HTTPError for bad responses (4xx or 5xx)

        # 3. Parse the JSON data
        data = response.json()

        print(f"API Message: {data.get('message', 'No message provided')}")
        print("-" * 40)

        # 4. Extract and display the list of items
        items = data.get(item_key, [])

        if items:
            print(f"Found {len(items)} {item_key.capitalize()}:")
            display_formatter(items)
        else:
            print(f"The API returned data, but the '{item_key}' list was empty.")

    except requests.exceptions.ConnectionError:
        print("\n[ERROR] Connection Error: Could not connect to the Flask API.")
        print("Please ensure 'mock_flask_api.py' is running in another terminal window.")
    except requests.exceptions.RequestException as e:
        print(f"\n[ERROR] An error occurred during the request: {e}")
    except json.JSONDecodeError:
        print(f"\n[ERROR] Failed to decode JSON from the API response.")
        print(f"Received non-JSON content: {response.text[:50]}...")


# --- Specific Display Formatters ---

def display_products(products):
    """Formats and prints product details."""
    print("ID | Name                  | Price   | Stock")
    print("---|-----------------------|---------|-------")
    for product in products:
        product_id = product.get('id', 'N/A')
        name = product.get('name', 'N/A')
        price = product.get('price', 0.00)
        in_stock = "Yes" if product.get('in_stock', False) else "No"
        # Use string formatting to align the output
        print(f"{product_id:<2} | {name:<21} | ${price:<5.2f} | {in_stock}")

def display_orders(orders):
    """Formats and prints order history details (the new feature)."""
    print("Order ID    | Date       | Total    | Status")
    print("------------|------------|----------|----------")
    for order in orders:
        order_id = order.get('order_id', 'N/A')
        date = order.get('date', 'N/A')
        total = order.get('total', 0.00)
        status = order.get('status', 'N/A')
        print(f"{order_id:<11} | {date:<10} | ${total:<7.2f} | {status}")


# --- Main Application Logic ---

def fetch_all_data():
    """Orchestrates the fetching of all data endpoints."""
    print(f"--- API Client Initializing ---")

    # Fetch Product Data from /api/products
    safe_api_call(endpoint="products", item_key="products", display_formatter=display_products)

    # Fetch Order History from /api/orders (the new feature)
    safe_api_call(endpoint="orders", item_key="orders", display_formatter=display_orders)

    print("\n--- API Client Finished ---")


if __name__ == '__main__':
    # Renamed the main function to better reflect its new purpose
    fetch_all_data()
