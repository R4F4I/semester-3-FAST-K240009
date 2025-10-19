""" 


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
        



"""

from flask import Flask, jsonify
import time # For simulating latency

app = Flask(__name__)

# Mock data
mock_posts = [
    {"post_id": 1, "user_id": 101, "username": "Alice", "content": "Hello #world!", "likes": 15, "comments": ["Great post!", "Agreed"]},
    {"post_id": 2, "user_id": 102, "username": "Bob", "content": "Learning Flask is fun #python", "likes": 30, "comments": ["Indeed", "Keep it up"]},
    {"post_id": 3, "user_id": 101, "username": "Alice", "content": "Another post by Alice", "likes": 5, "comments": []},
]

mock_users = {
    101: {"user_id": 101, "username": "Alice", "followers": 500},
    102: {"user_id": 102, "username": "Bob", "followers": 250},
}

mock_stocks = {
    "GOOGL": {"ticker": "GOOGL", "price": 145.50},
    "MSFT": {"ticker": "MSFT", "price": 330.10},
}

mock_news = {"headline": "Tech stocks rally on positive inflation report."}


# Endpoint: GET /posts
@app.route('/posts', methods=['GET'])
def get_posts():
    return jsonify(mock_posts)

# Endpoint: GET /users/<user_id>
@app.route('/users/<int:user_id>', methods=['GET'])
def get_user(user_id):
    user = mock_users.get(user_id)
    if user:
        return jsonify(user)
    return jsonify({"error": "User not found"}), 404

# Endpoint: GET /stocks/<ticker> with simulated latency
@app.route('/stocks/<ticker>', methods=['GET'])
def get_stock_price(ticker):
    time.sleep(1) # Simulate network latency
    stock = mock_stocks.get(ticker.upper())
    if stock:
        return jsonify(stock)
    return jsonify({"error": "Stock not found"}), 404

# Endpoint: GET /news with simulated latency
@app.route('/news', methods=['GET'])
def get_news():
    time.sleep(2) # Simulate slower API
    return jsonify(mock_news)

# Endpoint: GET /exchange_rate/<base>/<target> with simulated latency
@app.route('/exchange_rate/<base>/<target>', methods=['GET'])
def get_exchange_rate(base, target):
    time.sleep(1.5) # Simulate latency
    # Dummy logic for rates
    rates = {
        ("USD", "EUR"): 0.92,
        ("EUR", "USD"): 1.08,
    }
    rate = rates.get((base.upper(), target.upper()))
    if rate is not None:
        return jsonify({"base": base.upper(), "target": target.upper(), "rate": rate})
    return jsonify({"error": "Exchange rate not available"}), 404

if __name__ == '__main__':
    # Run the Flask app on host 127.0.0.1 (localhost) and port 5000
    print("Mock API running on http://127.0.0.1:5000/")
    print("Example endpoints:")
    print(" - http://127.0.0.1:5000/posts")
    print(" - http://127.0.0.1:5000/users/101")
    print(" - http://127.0.0.1:5000/stocks/GOOGL")
    print(" - http://127.0.0.1:5000/news")
    print(" - http://127.0.0.1:5000/exchange_rate/USD/EUR")
    app.run(debug=True) # debug=True enables auto-reloading and better error messages