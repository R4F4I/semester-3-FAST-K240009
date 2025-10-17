# --------------------------------------------------------------------------
# File: mock_flask_api.py
# Description: A simple Flask application that simulates a public API endpoint.
# It returns JSON objects for products and order history.
# --------------------------------------------------------------------------
from flask import Flask, jsonify

# Initialize the Flask application
app = Flask(__name__)

# Sample data to be returned by the API
PRODUCT_DATA = [
    {"id": 101, "name": "Gemini Mug", "price": 19.99, "in_stock": True},
    {"id": 102, "name": "Quantum Keyboard", "price": 125.00, "in_stock": False},
    {"id": 103, "name": "AI Notebook", "price": 4.50, "in_stock": True},
    {"id": 104, "name": "LLM Desk Mat", "price": 35.99, "in_stock": True},
]

# NEW MOCK DATA: Order History (Non-sensitive replacement)
ORDER_DATA = [
    {"order_id": "ORD-001", "date": "2024-05-01", "total": 59.97, "status": "Shipped"},
    {"order_id": "ORD-002", "date": "2024-05-15", "total": 125.00, "status": "Processing"},
    {"order_id": "ORD-003", "date": "2024-05-20", "total": 4.50, "status": "Delivered"},
]

@app.route('/api/products', methods=['GET'])
def get_products():
    """
    API endpoint to return the list of products as a JSON response.
    """
    # The jsonify function returns a Response object with the JSON data
    # and the application/json MIME type, which is what the client expects.
    return jsonify({
        "status": "success",
        "message": "Product list fetched successfully",
        "products": PRODUCT_DATA
    })

@app.route('/api/orders', methods=['GET'])
def get_orders():
    """
    NEW API endpoint to return the list of non-sensitive orders as a JSON response.
    """
    return jsonify({
        "status": "success",
        "message": "Order history fetched successfully",
        "orders": ORDER_DATA
    })


@app.route('/')
def home():
    """Simple homepage for the API."""
    return "The mock API server is running! Access /api/products or /api/orders to see the data."

if __name__ == '__main__':
    # Run the application on localhost and port 5000
    # You must run this file first and keep it running before executing api_client.py
    print("Running Flask API Server on http://127.0.0.1:5000/")
    app.run(debug=True, port=5000)
