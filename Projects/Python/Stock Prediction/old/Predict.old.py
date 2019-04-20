import numpy as np
import random as rand
import matplotlib.pyplot as plt
from pandas_datareader import data
import pandas as pd
from datetime import datetime
from dateutil.relativedelta import relativedelta

# Rework to provide accurate information


if __name__ == '__main__':
    ticker = 'UGAZ'
    P = 10;
    ref = data.DataReader(ticker, 'yahoo', str(datetime.today() + relativedelta(days=-3 * P)).split(' ')[0], str(datetime.today()).split(' ')[0])['Open']
    day = ref.keys()
    price = np.array(ref)
    fut_growth_percent = np.diff(price) / price[0 : len(price) - 1] * 100.0

    A = price[-P::]
    temp = price
    for i in np.arange(1, P):
        der = np.diff(temp)
        A = np.vstack((A, der[-P::]))
        temp = der
    A = A.transpose()

    a = fut_growth_percent[-P::]

    coef = np.mat((np.array(np.linalg.lstsq(A, a, rcond=None)))[0]).transpose()

    exp_fut_growth_percent = A * coef

    p = price[len(price) - 1 - P : len(price) - 1]
    e = np.resize(exp_fut_growth_percent[-P::], P)

    pred_p = np.array(p) * np.array(e / 100.0 + 1)

    plt.plot(day[-P::], p, label='Price')
    plt.plot(day[len(day) - 1 - (P - 1) : len(day) - 1], pred_p[-(P - 1)::], label='Predicted Price')
    plt.plot(day[-P::], a, label='Future Growth (%)')
    plt.plot(day[-P::], e, label='Expected Growth (%)')
    plt.legend()
    plt.grid()
    plt.show()
