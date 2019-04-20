import os
import pandas as pd
from pandas_datareader import data as web   # Package and modules for importing data; this code may change depending on pandas version
import datetime
from sklearn.linear_model import LinearRegression
import numpy as np

# Setting up the model
linreg = LinearRegression()
# Collecting stock tickers we are interested in
t = web.get_nasdaq_symbols()
t = t[t['Financial Status'] == 'N']
t = t[t['Listing Exchange'] == 'Q']
t = t[t['Test Issue'] == False]
tickers = t.index.values
money = 10000
portfolio = dict((t, 0) for t in tickers)
currPrice = dict((t, 0) for t in tickers)

def evaulateForTrade(ticker, start, end):
    # First argument is the series we want, second is the source ("yahoo" for Yahoo! Finance), third is the start date, fourth is the end date
    try:
        stock = web.DataReader(ticker, "yahoo", start, end)
        type(stock)
        close = stock['Adj Close'].values[-10:]
        x = np.arange(1, len(close) + 1).reshape(-1, 1)
        linreg.fit(x, close)
        if (linreg.coef_ > 0):
            return True
    except Exception as e:
        pass
    return False

def trade(ticker, date, buy, quantity):
    global money
    try:
        price = web.DataReader(ticker, "yahoo", date, date)['Adj Close'].values[0]
        currPrice[ticker] = price
        if buy:
            if (money < quantity * price):
                quantity = floor(money / price)
            portfolio[ticker] += quantity
            money -= price * quantity
        else:
            if (portfolio[ticker] < quantity):
                quantity = portfolio[ticker]
            portfolio[ticker] -= quantity
            money += price * quantity
    except Exception as e:
        pass

if __name__ == '__main__':

    # We will look at stock prices starting at January 1, 2000
    start = datetime.datetime(2000, 1, 1)
    delta = datetime.timedelta(days=1)
    end = start + delta
    while (end <= datetime.datetime.today() - delta):

        sum = 0;
        for ticker in tickers[0:5]:
            sum += currPrice[ticker] * portfolio[ticker]

        print('Date: ' + str(end + delta))
        print('Money: ' + str(money))
        print('Evaluation: ' + str(money + sum))

        for ticker in tickers[0:5]:
            # print(ticker + '\r')
            if (evaulateForTrade(ticker, start, end)):
                # Increase means buy
                trade(ticker, end + delta, True, 1)
            else:
                # Decrease means sell
                trade(ticker, end + delta, False, 1)

        end += delta

    # for ticker in tickers:
    #     print(evaulate(ticker) + ' ' + ticker)
