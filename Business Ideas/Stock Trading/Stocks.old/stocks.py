# Works fairly well
# Author: Seth Peden
# Data: 04-15-2019

import numpy as np
from pandas_datareader import data as pdData
import pandas as pd
from datetime import datetime
from dateutil.relativedelta import relativedelta
import matplotlib.pyplot as plt
import sys
import random

def getSymbols(N):
    table = pd.read_html('https://en.wikipedia.org/wiki/List_of_S%26P_500_companies')[0]
    sliced_table = table[1:]
    header = table.iloc[0]
    corrected_table = sliced_table.rename(columns=header)
    tickers = corrected_table['Symbol'].tolist()
    return tickers[0 : N]

def getData(tickers, M):
    data = {}
    for ticker in tickers:
        data[ticker] = pdData.DataReader(ticker, 'yahoo', str(datetime.today() - relativedelta(months=M)).split(' ')[0], str(datetime.today()).split(' ')[0])['Close']
    return data

def splitData(price, tickers):
    trainData = {}
    testData = {}
    simData = {}
    L = len(price[tickers[0]])
    for ticker in tickers:
        trainData[ticker] = price[ticker][0:L / 3]
        testData[ticker] = price[ticker][L / 3:2 * L / 3]
        simData[ticker] = price[ticker][2 * L / 3:L]
    return trainData, testData, simData

def normalize(price):
    return price / price[0]

def createTrainingData(price, hist, threshold):
    training = { 'x' : [], 'y' : [] }
    for ticker in price.keys():
        close = normalize(price[ticker])
        for i in np.arange(hist, len(close)):
            training['x'] = np.array(close[i - hist : i]) if training['x'] == [] else np.vstack((training['x'], np.array(close[i - hist : i])))
            training['y'] = (np.array(threshold) if close[i] > close[i - 1] else np.array(-threshold)) if training['y'] == [] else np.vstack((training['y'], (np.array(threshold) if close[i] > close[i - 1] else np.array(-threshold))))
    return training

def test(test, model, threshold):
    score = 0
    for i in np.arange(0, len(test['x'])):
        pred = np.sum(test['x'][i] * model)
        if pred * test['y'][i] > 0:
            score += 1
    return float(score) / len(test['x'])

def model(x_train, y_train):
    return np.reshape(np.linalg.lstsq(x_train, y_train, rcond=None)[0], len(x_train[0]))

def getReccomendations(tickers):
    recc = { 'buy' : [], 'sell' : [] }
    data = getData(tickers, 6)
    best = [0, 0]
    T = 50
    for d in np.arange(2, 5):
        training = createTrainingData(data, d, T)
        M = model(training['x'], training['y'])
        S = test(training, M, T)
        if S > best[0]:
            best = [S, d]
    D = best[1]
    training = createTrainingData(data, D, T)
    M = model(training['x'], training['y'])
    for ticker in tickers:
        slice = data[ticker][-D::]
        S = np.sum(slice * M)
        if S > T / 5:
            recc['buy'].append(ticker)
        elif S < -T / 5:
            recc['sell'].append(ticker)
    recc['D'] = D
    recc['data'] = data
    return recc

def main():
    tickers = ['AAPL', 'FB', 'SNAP', 'TSLA', 'F', 'GM', 'FCAU', 'UGAZ', 'DGAZ']
    # tickers = getSymbols(25)
    print(getReccomendations(tickers))
    # tickers = getSymbols(10)
    # price = getData(tickers, 12)
    # I = len(price[tickers[0]])
    # growth = 1.0
    # for i in np.arange(I / 4, I):
    #     print 'Step: {} / {}'.format(i - I / 4 + 1, 3 * I / 4 + 1)
    #     data = {}
    #     for ticker in tickers:
    #         data[ticker] = price[ticker][i - I / 4 : i]
    #     trainData, testData, simData = splitData(data, tickers)
    #     best = [0, 0]
    #     T = 50
    #     for d in np.arange(1, 5):
    #         training = createTrainingData(trainData, d, T)
    #         testing = createTrainingData(testData, d, T)
    #         M = model(training['x'], training['y'])
    #         S = test(testing, M, T)
    #         if S > best[0]:
    #             best = [S, d]
    #     D = best[1]
    #     training = createTrainingData(trainData, D, T)
    #     testing = createTrainingData(testData, D, T)
    #     M = model(training['x'], training['y'])
    #     S = test(testing, M, T)
    #
    #     g = 0.0
    #     for ticker in tickers:
    #         slice = simData[ticker]
    #         slice = slice[0 : len(slice) - 1][-D::]
    #         pred = np.sum(slice * M)
    #         if pred > 0:
    #             g += simData[ticker][len(simData)] / simData[ticker][len(simData) - 1]
    #         else:
    #             g += 1.0
    #     growth *= g / len(tickers)
    # print '{}% growth.'.format((growth - 1.0) * 100.0)

if __name__ == '__main__':
    main()
