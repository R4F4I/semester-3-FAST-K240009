---
aliases: []
tags: []
type:
  - notes
note-level: 1
status: incomplete
title: readme
author: Rafay Siddiqui
abstract: this is an abstract
description:
date: October 16, 2025
datenum: 20251016
day: Thursday
time: 16:49
UNIX timestamp: 1760615397
cssclasses:
  - center-titles
  - image-borders
updated_at: 2025-09-28T23:23:58.755+05:00
edited_seconds: 10
---


# readme

---

### 🧠 Problem 1: The Smart-Trading Bot Simulator

**Concept:** Design a simulation of a stock market where a trading bot makes decisions based on market fluctuations. This problem will test your understanding of object-oriented design, data manipulation, and implementing logic-based interactions between objects.

**Description:**

You are tasked with building a `Smart-Trading Bot Simulator`. This involves creating a system with three main components: a `Trader`, a `Stock`, and a `Market`.

**Core Classes:**

1.  **`Stock` Class:**
    
    -   **Attributes:** `name` (string), `ticker` (string), `initial_price` (float), `current_price` (float), `volatility` (float, a measure of how much the price can change, e.g., 0.05 for 5%).
    -   **Method:** `update_price()`: This method should simulate a price change. The new price should be calculated based on the `current_price` and `volatility`. The change can be a random increase or decrease within the `volatility` range.
        
2.  **`Trader` Class:**
    
    -   **Attributes:** `name` (string), `initial_capital` (float), `current_capital` (float), `portfolio` (a dictionary where keys are stock tickers and values are the number of shares owned).
    -   **Methods:**
        
        -   `buy(stock, quantity)`: Allows the `trader` to buy a certain `quantity` of a `stock`. This should decrease the `trader`'s `current_capital` and update the `portfolio`. A `trader` cannot buy if they don't have enough `capital`.
        -   `sell(stock, quantity)`: Allows the `trader` to sell a certain `quantity` of a `stock`. This should increase the `current_capital` and update the `portfolio`. A `trader` cannot sell shares they don't own.
        -   `evaluate_portfolio(market)`: Calculates the current total value of the `trader`'s `portfolio` based on the `current_prices` of the `stocks` in the given `market`.
            
3.  **`Market` Class:**
    
    -   **Attributes:** `name` (string), `stocks` (a dictionary of `Stock` objects, with `tickers` as keys).
    -   **Methods:**
		-   `add_stock(stock)`: Adds a new `stock` to the `market`.
		-   `simulate_day()`: This is the core of the simulation. For each `stock` in the `market`, it should call the `update_price()` method. It should then print a summary of the `market`'s activity for the day.
		-   `get_stock(ticker)`: Retrieves a `stock` by its `ticker`.


**Challenge:**

Create a simulation that runs for 30 "days."

1.  Initialize a `Market` with at least 5 different `stocks`, each with a unique `volatility`.
2.  Initialize a `Trader` with a starting `capital`.
3.  For each day of the simulation:
    -   The `Market` updates the `prices` of all `stocks`.
    -   The `Trader` bot must decide whether to buy or sell `stocks` based on a simple algorithm of your choice. For example, it could buy a `stock` if its `price` drops by more than 5% in a day, or sell if it rises by more than 7%.
    -   Print out the `trader`'s actions for the day and the end-of-day value of their `portfolio`.
4.  At the end of the 30 days, report the `trader`'s final `capital` and total `portfolio` value.

---

### 🌐 Problem 2: The Social Media Analyzer API

**Concept:** This problem introduces working with a mock API. You'll need to fetch data from a simulated API, process it using your object-oriented skills, and perform some analysis.

**Description:**

Imagine you have access to a social media platform's API. You need to build a tool that can analyze posts to find trending topics and the most influential users.

**The Mock API:**

You will need to create a simple mock API. You can do this using a library like **`Flask`**. The API should have the following endpoints:
-   **`GET /posts`**: Returns a JSON list of post objects. Each post object should have:
    
    -   `post_id`: integer
    -   `user_id`: integer
    -   `username`: string
    -   `content`: string (the text of the post)
    -   `likes`: integer
    -   `comments`: a list of strings
        
-   **`GET /users/<user_id>`**: Returns a JSON object with details about a specific user:
    
    -   `user_id`: integer
    -   `username`: string
    -   `followers`: integer
        

**Core Classes:**

1.  **`Post` Class:**
    
    -   **Attributes:** `post_id`, `user_id`, `username`, `content`, `likes`, `comments`.
    -   **Method:** `calculate_engagement_score()`: This method should return a score based on `likes` and `comments`. A simple formula could be `(likes * 0.3) + (len(comments) * 0.7)`.
        
2.  **`SocialMediaAnalyzer` Class:**
    
    -   **Attributes:** `api_base_url` (the URL of your mock API).
    -   **Methods:**
        
        -   `fetch_posts()`: Fetches all posts from the `/posts` endpoint and returns a list of `Post` objects.
        -   `find_trending_topics()`: Analyzes the `content` of all posts to find the most frequently mentioned words or hashtags (e.g., words starting with '#'). It should return a dictionary of `topics` and their `frequencies`.
        -   `get_most_influential_users(top_n=5)`: This is the most complex method. It should:
            
            1.  Fetch all posts.
            2.  For each post, calculate its `engagement_score`.
            3.  Group the `engagement_scores` by `user_id`.
            4.  For each user, fetch their `follower_count` from the `/users/<user_id>` endpoint.
            5.  Calculate an "influence score" for each user. A possible formula: `(total_engagement_score * 0.4) + (followers * 0.6)`.
            6.  Return a list of the top `n` users based on their `influence_score`.
                

**Challenge:**

1.  Build and run the `Flask` mock API with some sample data (at least 20 posts and 10 users).
2.  Implement the `Post` and `SocialMediaAnalyzer` classes.
3.  Write a script that uses the `SocialMediaAnalyzer` to:
    
    -   Fetch all posts.
    -   Display the top 10 trending topics.
    -   Display the top 5 most influential users, showing their `username` and `influence_score`.
        

---

### 🚀 Problem 3: The Multi-threaded Stock Market Dashboard

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



### 🌋 Problem 6: Geospatial Earthquake Hotspot Analysis

**Concept:** This problem involves fetching real-world earthquake data from the U.S. Geological Survey (USGS) API. You will use `numpy` to perform geospatial calculations to identify and analyze earthquake hotspots relative to a major city. This tests your ability to work with coordinate data, perform complex mathematical operations on arrays, and structure a data analysis pipeline.

**Description:**

You are a seismologist analyzing seismic activity in the Pacific Ring of Fire. Your goal is to fetch data on all earthquakes that occurred in the last month and determine their proximity to a major city, like Tokyo, Japan. You need to calculate the distance of each earthquake from Tokyo and identify the most significant seismic events.

**Public API to Use:**
- **USGS Earthquake Catalog API:** Provides real-time and historical earthquake data.
- **Endpoint for the last 30 days:** `https://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/all_month.geojson`


**Core Classes:**
1. **`EarthquakeApiClient` Class:**
    - **Attributes:** `api_url` (the USGS endpoint).
    - **Method:** `fetch_earthquake_data()`:
        - Makes a GET request to the API.
        - Parses the GeoJSON response (which is a type of JSON). The earthquake data is located under the `"features"` key.
        - Iterates through the features and extracts the magnitude, depth, latitude, and longitude for each earthquake.
        - **Compiles this data into a single 2D `numpy` array** where each row represents an earthquake and the columns are `[latitude, longitude, depth, magnitude]`.
        - Returns this `numpy` array.
2. **`GeoSpatialAnalyzer` Class:**
    - **Attributes:** `earthquake_data` (the `numpy` array from the client), `city_coords` (a tuple representing the target city's latitude and longitude, e.g., Tokyo at `(35.6895, 139.6917)`
    - **Methods:**
        - `filter_by_magnitude(min_magnitude)`:
            - Uses `numpy`'s boolean indexing to select and return only the rows (earthquakes) from `earthquake_data` that have a magnitude greater than or equal to `min_magnitude`.
        - `calculate_distances_from_city()`:
            - This is the core `numpy` challenge. You must implement the **Haversine formula** to calculate the distance in kilometers between the city and _every earthquake in the dataset simultaneously_ using vectorized operations.
            - The formula requires converting latitudes and longitudes to radians (`np.radians`).
            - The Haversine formula:
                $a=\sin^2(2Δϕ​)+\cos(ϕ_{1}​)\cos(ϕ_{2}​)\sin^2(2Δλ​)$
                c=2⋅atan2(a​,1−a​)
                d=R⋅c
                (where ϕ is latitude, λ is longitude, R is the Earth's radius (6371 km), and Δ is the difference).
            - This method should return a new 1D `numpy` array containing the distance of each earthquake from the city.
        - `find_closest_event(filtered_data, distances)`:
            - Finds the index of the minimum value in the `distances` array using `np.argmin`.
            - Uses this index to retrieve the corresponding earthquake's data (lat, long, depth, mag) from the `filtered_data` array.
            - Returns the data of the closest significant earthquake.

**Challenge:**
1. Implement the `EarthquakeApiClient` and `GeoSpatialAnalyzer` classes.
2. Write a main script that:
    - Initializes the API client and fetches the earthquake data for the last 30 days.
    - Initializes the analyzer with the fetched data and the coordinates for Tokyo.
    - Filters the data to only include earthquakes with a magnitude of 4.5 or greater.
    - Calculates the distances of these significant earthquakes from Tokyo using your vectorized Haversine implementation.
    - Identifies the top 5 most powerful (highest magnitude) earthquakes within a 1500 km radius of Tokyo.
    - Finds the single closest earthquake (of magnitude 4.5+) to Tokyo.
    - Prints a summary report detailing the total number of significant earthquakes, the details of the top 5 most powerful nearby events, and the details of the closest event.

---

### ☀️ Problem 7: Historical Climate Trend Analyzer

**Concept:** This problem involves fetching a large time-series dataset of historical weather data from a public meteorology API. You will use `numpy` to perform sophisticated statistical analysis to identify long-term climate trends, seasonal patterns, and temperature anomalies.

**Description:**

You are a climate scientist studying weather patterns in Karachi, Pakistan. Your task is to fetch 30 years of daily weather data (from 1994 to 2024) and analyze it for trends, including average temperature changes, precipitation patterns, and identifying extreme weather events.

**Public API to Use:**

- **Open-Meteo Historical Weather API:** A free, open-source API with no key required. It provides a vast amount of historical weather data.
- **Endpoint:** `https://archive-api.open-meteo.com/v1/archive`
- Example URL for Karachi (Latitude: 24.86, Longitude: 67.01) from 1994 to 2024:
	- https://archive-api.open-meteo.com/v1/archive?latitude=24.86&longitude=67.01&start_date=1994-01-01&end_date=2024-01-01&daily=temperature_2m_max,temperature_2m_min,precipitation_sum

**Core Classes:**
1. **`ClimateDataClient` Class:**
    - **Attributes:** `base_url`.
    - **Method:** `fetch_historical_data(lat, lon, start_date, end_date)`:
        - Constructs the full API request URL with the given parameters.
        - Fetches the data. The response JSON will have a `"daily"` key containing lists for `"time"`, `"temperature_2m_max"`, etc.
        - **Converts the lists for max temperature, min temperature, and precipitation into three separate 1D `numpy` arrays.**
        - Returns the three `numpy` arrays.
2. **`TrendAnalyzer` Class:**
    - **Attributes:** `max_temps`, `min_temps`, `precipitation` (the three `numpy` arrays). The data is daily, so you can assume a 365-day year for reshaping.
    - **Methods:**
        - `calculate_annual_averages()`:
            - Reshapes the 1D temperature arrays into 2D arrays where each row is a year and each column is a day (e.g., `(30, 365)` for 30 years).
            - Uses `numpy`'s `mean` function with `axis=1` to calculate the average maximum temperature for each year.
            - Returns a 1D array of annual average temperatures.
        - `find_hottest_days(top_n=10)`:
            - Uses `np.argsort` on the `max_temps` array to find the indices of the `top_n` hottest days in the entire 30-year period.
            - Returns the temperatures and indices of these days. (You would need the original time data to map indices back to dates).
        - `calculate_seasonal_precipitation()`:
            - Reshapes the 1D precipitation array into the `(30, 365)` 2D array.
            - Uses `numpy` slicing to define seasons (e.g., Summer/Monsoon: days 152-273).
            - Calculates the total precipitation for the monsoon season for each of the 30 years using `np.sum` on the slices with `axis=1`.
            - Returns a 1D array of total monsoon precipitation for each year.
        - `detect_anomalies(std_dev_threshold=2.5)`:
            - Calculates the overall mean and standard deviation of the entire `max_temps` dataset.
            - Uses boolean masking to identify all days where the temperature was more than `std_dev_threshold` standard deviations above the mean.
            - Returns a `numpy` array of these anomalous high temperatures.

**Challenge:**
1. Implement the `ClimateDataClient` and `TrendAnalyzer` classes.
2. Write a main script that:
    - Fetches the 30-year daily weather data for Karachi.
    - Initializes the `TrendAnalyzer` with the fetched `numpy` arrays.
    - Calculates and prints the average maximum temperature for each year from 1994 to 2023.
    - Finds and prints the dates and temperatures of the 10 hottest days recorded in the 30-year period.
    - Calculates and prints the total monsoon season precipitation for each year to observe any trends.
    - Detects and prints the number of "extreme heat" days (anomalies) found in the dataset.
    - Concludes with a short summary of whether the data suggests a warming trend or changes in monsoon intensity over the 30 years.