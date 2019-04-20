from LTSPrediction import LTSPredictor
import numpy as np
import matplotlib.pyplot as plt
from pandas_datareader import data as pdData
from datetime import datetime
from dateutil.relativedelta import relativedelta
import sys

def shouldBuy(data):
    n = np.arange(0, len(data))

    p = 0.25
    pred = LTSPredictor(predictions=int((1.0 - p) * len(data) / 10), reflection=int(len(data) * (1.0 - p)))
    pred.train(data)
    prediction = pred.predict(data)

    N = len(prediction) + pred.reflection - len(data)
    M = np.mean(prediction[-N:])

    return bool(M > data[-1:])

for i in np.arange(1, len(sys.argv)):
    ticker = sys.argv[i]
    stock_data = np.array(pdData.DataReader(ticker, 'yahoo', str(datetime.today() - relativedelta(months=96)).split(' ')[0], str(datetime.today()).split(' ')[0])['Close'])
    k = np.arange(0, len(stock_data))

    L = len(stock_data)
    NB = np.array([])
    B = np.array([])
    NS = np.array([])
    S = np.array([])
    for n in np.arange(L / 2, L):
        data = stock_data[0 : n]
        if shouldBuy(data):
            NB = np.append(NB, n)
            B = np.append(B, data[-1:])
        else:
            NS = np.append(NS, n)
            S = np.append(S, data[-1:])

    NO = np.arange(L / 2, L)
    O = np.zeros(len(NO))
    for n in NO:
        if np.sum(O) == 0 and np.any(NB == n):
            O[n - L / 2] = -1
        elif np.sum(O) == -1 and np.any(NS == n):
            O[n - L / 2] = 1
    O[-1:] = 1 if np.sum(O) == -1 else 0

    PPS = np.sum(stock_data[L / 2 : L] * O)

    print PPS

    NB = []
    B = []
    NS = []
    S = []

    for n in NO:
        if O[n - L / 2] == -1:
            NB = np.append(NB, n)
            B = np.append(B, stock_data[n])
        elif O[n - L / 2] == 1:
            NS = np.append(NS, n)
            S = np.append(S, stock_data[n])

    plt.plot(k, stock_data, label='Data')
    plt.scatter(NB, B, label='Buy')
    plt.scatter(NS, S, label='Sell')

    plt.title(ticker)
    plt.legend()
    plt.show()
