# 1. IMPORTS
from flask import Flask, jsonify
import time

# 2. INITIALIZATION
app = Flask(__name__)

# 3. SAMPLE DATA
# This data will be returned as the JSON payload.
sample_data = {
    "status": "active",
    "generation_time": int(time.time()),
    "message": "Simple JSON API response from local Flask server.",
    "inventory_items": [
        {"id": 501, "item_name": "Keyboard", "price_usd": 75.00, "in_stock": True},
        {"id": 502, "item_name": "Mouse", "price_usd": 25.50, "in_stock": True},
        {"id": 503, "item_name": "Monitor", "price_usd": 299.99, "in_stock": False},
        {"id": 504, "item_name": "Webcam", "price_usd": 50.00, "in_stock": True},
    ]
}

# 4. API ENDPOINTS

@app.route("/")
def index():
    """Default route for instructions."""
    return "<h1>Local Flask Server Running</h1><p>Visit the /data endpoint for the JSON output: <a href='/data'>http://127.0.0.1:5000/data</a></p>"

@app.route("/data", methods=["GET"])
def handle_data():
    """Returns the structured sample data as a JSON response."""
    return jsonify(sample_data)

@app.route("/test", methods=["GET"])
def show_something():
    return "<h1>Local Flask Server Running</h1><p>Visit the /data endpoint for the JSON output: <a href='/data'>http://127.0.0.1:5000/data</a></p>"
    

# 5. RUN APPLICATION
if __name__ == '__main__':
    # Runs the application on localhost (127.0.0.1:5000) with debug mode enabled.
    app.run(debug=True)
