import numpy as np
import random as rand
import matplotlib.pyplot as plt
from pandas_datareader import data
import pandas as pd
from datetime import datetime
from dateutil.relativedelta import relativedelta


if __name__ == '__main__':
    ticker = 'UGAZ'
    P = 4;
    ref = data.DataReader(ticker, 'yahoo', str(datetime.today() + relativedelta(days=(-10 * P))).split(' ')[0], str(datetime.today()).split(' ')[0])['Open']
    day = ref.keys()
    price = np.array(ref)
    N = len(price)
    n = np.arange(N)

    A = price[0 : P]
    for i in np.arange(1, N - P):
        A = np.vstack((A, price[i : P + i]))

    fut = np.mat(price[P : N]).transpose()

    x = np.mat((np.array(np.linalg.lstsq(A, fut, rcond=None)))[0])

    pred = A * x

    plt.plot(n, price, label='Price')
    plt.plot(n[-(N - P)::], fut, label='Future Price')
    plt.plot(n[P - 1 : N - 1], pred, label='Expected Price')

    min = np.min(price)
    max = np.max(price)
    for i in np.arange(0, N, 4):
        plt.plot([i, i], [min, max], color = 'black')
    for i in np.arange(min, max, 4):
        plt.plot([0, N], [i, i], color = 'black')

    plt.legend()
    plt.show()
