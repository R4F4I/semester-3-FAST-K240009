""" 



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



"""

import random

class Stock:
    def __init__(self,name = "",ticker = "",init_price = 0.0,curr_price = 0.0,volatility = 0.0):
        self.name = name
        self.ticker = ticker
        self.init_price = init_price
        self.curr_price = curr_price
        self.volatility = volatility
    
    def update_price(self):
        randNum = random.randint(0,1)
        if randNum == 1:
            # increase the price
            self.curr_price += self.curr_price*self.volatility 
        else :
            # decrease the price
            self.curr_price -= self.curr_price*self.volatility 


class Trader:
    def __init__(self,name = "",init_cap = 0,curr_cap = 0,portfolio = {}):
        self.name = name
        self.init_cap = init_cap
        self.curr_cap = curr_cap
        self.portfolio = portfolio

    def buy(self,market,ticker,quantity):
        self.portfolio[ticker] += quantity

        for stock in market.stocks:
            if stock.ticker == ticker:
                self.curr_cap -= stock.curr_price
    
    def sell(self,market,ticker,quantity):
        self.portfolio[ticker] -= quantity

        # update cash in hand
        for stock in market.stocks:
            if stock.ticker == ticker:
                self.curr_cap += stock.curr_price
    
    
    
    def eval_portfolio(market):
        totalSum = 0
        for stock in market.stocks:
            totalSum += stock.curr_price
        return totalSum
    
    def determine_deal(self,market,stock):

        if (stock.volatility > 0.07 or self.curr_cap < 10):
        
            self.sell(market,stock.ticker,1)
            print(f"sold 1 {stock.name}")
            print(f"cash in hand: {self.curr_cap}")
            stock.volatility -=0.001
        
        if stock.volatility < 0.05:
        
            self.buy(market,stock.ticker,1)
            print(f"bought 1 {stock.name}")
            print(f"cash in hand: {self.curr_cap}")
            # buying changes its volatility
            stock.volatility +=0.001
        
    



class Market:
    def __init__(self,name,stocks):
        self.name = name
        self.stocks = stocks
    
    def simulate_day(self,day):
        for stock in self.stocks:
            stock.update_price()
            print("-----------------------------")
            print(f"day {day}'s activity:")
            print("-----------------------------")
            # print("stock name:",stock.name, "stock ticker:",stock.ticker, "stock init_price:",stock.init_price, "stock curr_price:",stock.curr_price, "stock volatility:",stock.volatility)
    
    def get_stock(self, targetTicker):
        for stock in self.stocks:
            if stock.ticker == targetTicker:
                return stock


Stock1 = Stock("AAPL","qwe0",213.1,415.1,0.01)
Stock2 = Stock("ABPL","qwe1",223.1,425.1,0.03)
Stock3 = Stock("ACPL","qwe2",233.1,435.1,0.05)
Stock4 = Stock("ADPL","qwe3",243.1,445.1,0.07)
Stock5 = Stock("AEPL","qwe4",253.1,455.1,0.09)



market = Market("silicon",[Stock1,Stock2,Stock3,Stock4,Stock4])

trader = Trader("steve",0, 1000,
    {
        "qwe0": 33,
        "qwe1": 42,
        "qwe2": 13,
        "qwe3": 14,
    } 
)

for i in range(30):
    market.simulate_day(i)
    for stock in market.stocks:
        # print("stock.name: ",stock.name)
        trader.determine_deal(market,stock)
    print("\n\n")
