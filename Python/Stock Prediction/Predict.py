import numpy as np
from pandas_datareader import data
import pandas as pd
from datetime import datetime
from dateutil.relativedelta import relativedelta
import matplotlib.pyplot as plt
import sys

def simulate(ticker, M, W):
    today = datetime.today()
    stock = data.DataReader(ticker, 'yahoo', str(today + relativedelta(months=-M)).split(' ')[0], str(today).split(' ')[0])['Close']
    close = np.array(stock)
    date = stock.keys()
    N = len(close)
    n = np.arange(0, N)
    avg = map(lambda n: np.mean(close[max(0, n - W + 1) : n + 1]), n)

    above = np.array(list(elem for elem in map(lambda n: n if (avg < close)[n] else -1, n) if elem != -1))
    buy = np.array(list(elem for elem in above if not np.any(above == elem - 1)))

    below = np.array(list(elem for elem in map(lambda n: n if (avg > close)[n] else -1, n) if elem != -1))
    sell = np.array(list(elem for elem in below if not np.any(below == elem - 1)))

    if (buy[0] > sell[0]):
        sell = np.delete(sell, [0])
    if (len(buy) > len(sell)):
        sell = np.append(sell, buy[len(buy) - 1])

    buy_prices = close[buy]
    sell_prices = close[sell]

    growth_month = np.prod(sell_prices[0 : min(len(sell), len(buy))] / buy_prices[0 : min(len(sell), len(buy))]) / M

    return date, close, avg, sell, buy, growth_month

if __name__ == '__main__':
    if len(sys.argv) < 4:
        print('Usage: python Predict.py <ticker>')
    else:
        tickers = sys.argv[1 : len(sys.argv)]

        for ticker in tickers:
            fastest_growth = -1000000
            best_m = 0
            best_w = 0
            for M in np.arange(1, 36):
                for W in np.arange(2, 33, 10):
                    date, close, avg, sell, buy, growth_month = simulate(ticker, M, W)
                    if growth_month > fastest_growth:
                        fastest_growth = growth_month
                        best_m = M
                        best_w = W
                    print('M: ' + str(M) + ', W: ' + str(W) + ', Best: m=' + str(best_m) + ' w=' + str(best_w) + ' g=' + str(int((fastest_growth - 1) * 100.0)) + '%')

            print('For Ticker: ' + ticker)
            print('Best Growth: ' + str(int((fastest_growth - 1.0) * 100.0)) + '%')
            print('With M: ' + str(best_m) + ', W: ' + str(best_w))
            print('')
