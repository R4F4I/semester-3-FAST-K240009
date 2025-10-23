""" 


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
                
                c=2⋅atan2(a,1−a)
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


 """

import requests
import json
import numpy as np

api = "https://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/all_month.geojson"

class EarthquakeApiClient:
    """
    Fetches and processes earthquake data from the USGS API.
    """
    def __init__(self, api_url):
        self.api_url = api_url
        print(f"Initializing client for API: {self.api_url}\n")

    def fetch_earthquake_data(self):
        """
        Fetches earthquake data and compiles it into a NumPy array.
        
        Returns:
            numpy.ndarray: A 2D array where each row is an earthquake
                           and columns are [latitude, longitude, depth, magnitude].
                           Returns None if the request fails.
        """
        print("Fetching earthquake data from USGS...")
        try:
            response = requests.get(self.api_url, timeout=10)
            response.raise_for_status()  # Check for 4xx/5xx errors
            
            # --- START OF FIX ---
            # Instead of response.json(), we use json.loads(response.text).
            # This manually parses the text content and doesn't rely on
            # the server's 'Content-Type' header.
            
            if not response.text:
                print("Error: API returned an empty response.")
                return None
                
            try:
                # Manually parse the JSON from the response text
                data = json.loads(response.text)
            except json.JSONDecodeError as e:
                # This will trigger if the content is not valid JSON
                print(f"Error: Failed to decode JSON from response. {e}")
                print("--- Response Content (first 500 chars) ---")
                print(response.text[:500])
                print("------------------------------------------")
                return None
            # --- END OF FIX ---

            features = data.get('features', [])
            
            if not features:
                print("No earthquake 'features' found in parsed JSON data.")
                return None
                
            processed_data = []
            for feature in features:
                try:
                    coords = feature.get('geometry', {}).get('coordinates', [])
                    props = feature.get('properties', {})
                    
                    # GeoJSON format is [longitude, latitude, depth]
                    longitude = coords[0]
                    latitude = coords[1]
                    depth = coords[2]
                    magnitude = props.get('mag')
                    
                    # We only care about valid, complete entries
                    if all(isinstance(val, (int, float)) for val in [latitude, longitude, depth, magnitude]):
                        # Our array format: [latitude, longitude, depth, magnitude]
                        processed_data.append([latitude, longitude, depth, magnitude])
                
                except (IndexError, TypeError, KeyError):
                    # Skip any malformed feature
                    continue
            
            print(f"Successfully fetched and processed {len(processed_data)} earthquakes.")
            return np.array(processed_data)

        except requests.exceptions.RequestException as e:
            print(f"Error fetching data from API: {e}")
            return None

client = EarthquakeApiClient(api)
data = client.fetch_earthquake_data()

print(data)

