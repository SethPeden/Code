import numpy as np
from pandas_datareader import data
import pandas as pd
from datetime import datetime
from dateutil.relativedelta import relativedelta
import matplotlib.pyplot as plt
import sys
import random

BUY = -1
HOLD = 0
SELL = 1

CAN_BUY = 0
CAN_SELL = -1

def generate_order_list(price):
    N = len(price)
    list = np.array([])
    for i in np.arange(0, N):
        if np.sum(list) == CAN_BUY and price[min(i + 1, N - 1)] / price[i] > 1.0:
            list = np.append(list, BUY)
        elif np.sum(list) == CAN_SELL and price[min(i + 1, N - 1)] / price[i] < 1.0:
            list = np.append(list, SELL)
        else:
            list = np.append(list, HOLD)
    return list

def calc_growth(list, price):
    N = len(price)
    change = list * price
    principle = 5000
    account = principle
    shares = 0
    for j in np.arange(0, N):
        if change[j] < 0:
            shares = np.floor(account / -change[j])
            account += change[j] * shares
        elif change[j] > 0:
            account += change[j] * shares
            shares = 0
    if shares > 0:
        account += price[N - 1] * shares
        shares = 0
    growth = (account / principle - 1) * 100
    return growth

def find_best_order_list(price):
    list = generate_order_list(price)
    growth = calc_growth(list, price)
    return list, growth

T = 10000
def find_best_coeffecients(train_price, train_buy, train_sell, L):
    buy_thresh = 3 * np.mean(train_price) / 4
    sell_thresh = np.mean(train_price) / 4
    best = 0
    a = np.array([])
    for j in np.arange(0, T):
        score = 0
        b = np.random.rand(L, 1) * (2 * L) - L
        for i in np.arange(0, len(train_buy)):
            buy_index = train_buy[i]
            buy_history = train_price[0 : buy_index][-L::]
            if len(buy_history) < L:
                buy_history = np.append(np.zeros(L - len(buy_history)), buy_history)
            v = np.dot(buy_history, b)
            if v > buy_thresh:
                score += 1
        for i in np.arange(0, len(train_sell)):
            sell_index = train_sell[i]
            sell_history = train_price[0 : sell_index][-L::]
            if len(sell_history) < L:
                sell_history = np.append(np.zeros(L - len(sell_history)), sell_history)
            v = np.dot(sell_history, b)
            if v < sell_thresh:
                score += 1
        if score > best:
            best = score
            a = b
    return a, buy_thresh, sell_thresh

def find_order_list_with_thresh(price, a, buy_thresh, sell_thresh):
    N = len(a)
    list = np.array([])
    for i in np.arange(0, len(price)):
        history = price[0 : i][-N::]
        if len(history) < N:
            history = np.append(np.zeros(N - len(history)), history)
        v = np.dot(history, a)
        if v > buy_thresh:
            list = np.append(list, BUY)
        elif v < sell_thresh:
            list = np.append(list, SELL)
        else:
            list = np.append(list, HOLD)
    return list

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: python stocks.py <ticker>')
    else:
        ticker = sys.argv[1]
        train_close = data.DataReader(ticker, 'yahoo', str(datetime.today() - relativedelta(months=4)).split(' ')[0], str(datetime.today() - relativedelta(months=2)).split(' ')[0])['Close']
        train_date = train_close.keys()
        train_price = np.array(train_close)

        train_list, train_growth = find_best_order_list(train_price)

        train_n = np.arange(0, len(train_price))
        train_buy = filter(lambda n: n != -1, map(lambda n: n if train_list[n] == -1 else -1, train_n))
        train_sell = filter(lambda n: n != -1, map(lambda n: n if train_list[n] == 1 else -1, train_n))

        a, buy_thresh, sell_thresh = find_best_coeffecients(train_price, train_buy, train_sell, 10)

        print('A: ' + str(a))
        print('Buy Thresh: ' + str(buy_thresh))
        print('Sell Thresh: ' + str(sell_thresh))

        valid_close = data.DataReader(ticker, 'yahoo', str(datetime.today() - relativedelta(months=2)).split(' ')[0], str(datetime.today() - relativedelta(months=0)).split(' ')[0])['Close']
        valid_date = valid_close.keys()
        valid_price = np.array(valid_close)

        valid_list = find_order_list_with_thresh(valid_price, a, buy_thresh, sell_thresh)
        valid_growth = calc_growth(valid_list, valid_price)

        valid_n = np.arange(0, len(valid_price))
        valid_buy = filter(lambda n: n != -1, map(lambda n: n if valid_list[n] == -1 else -1, valid_n))
        valid_sell = filter(lambda n: n != -1, map(lambda n: n if valid_list[n] == 1 else -1, valid_n))

        print('List: ' + str(valid_list))
        print('Growth: ' + str(valid_growth))

        plt.plot(train_date, train_price, label='Training Closing Price')
        plt.scatter(train_date[train_buy], train_price[train_buy], label='Training Buy')
        plt.scatter(train_date[train_sell], train_price[train_sell], label='Training Sell')

        plt.plot(valid_date, valid_price, label='Validation Closing Price')
        plt.scatter(valid_date[valid_buy], valid_price[valid_buy], label='Validation Buy')
        plt.scatter(valid_date[valid_sell], valid_price[valid_sell], label='Validation Sell')

        plt.legend()
        plt.show()
