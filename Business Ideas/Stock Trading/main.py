from LTSPrediction import LTSPredictor
import numpy as np
import matplotlib.pyplot as plt
from pandas_datareader import data as pdData
from datetime import datetime
from dateutil.relativedelta import relativedelta
import sys

# def shouldBuy(data):
#     n = np.arange(0, len(data))
#
#     p = 0.25
#     pred = LTSPredictor(predictions=int((1.0 - p) * len(data) / 10), reflection=int(len(data) * (1.0 - p)))
#     pred.train(data)
#     prediction = pred.predict(data)
#
#     N = len(prediction) + pred.reflection - len(data)
#     M = np.mean(prediction[-N:])
#
#     return bool(M > data[-1:])

for i in np.arange(1, len(sys.argv)):
    ticker = sys.argv[i]
    stock_data = np.array(pdData.DataReader(ticker, 'yahoo', str(datetime.today() - relativedelta(months=4)).split(' ')[0], str(datetime.today()).split(' ')[0])['Close'])

    R = 10
    # Test
    temp = np.array([])
    for v in stock_data:
        temp = np.append(temp, v * np.ones(R,))
    stock_data = temp

    P = 10 * R
    data = stock_data[0 : len(stock_data) - P]
    n = np.arange(0, len(data))

    result = stock_data[-(P + 1):]
    l = np.arange(0, len(result)) + (len(data) - 1)

    pred = LTSPredictor(predictions=P, reflection=25)
    pred.train(data)
    prediction = pred.predict(data)
    m = np.arange(0, len(prediction)) + pred.reflection

    plt.plot(m, prediction, label='Prediction')
    plt.plot(n, data, label='Data')
    plt.plot(l, result, label='Result')

    plt.title(ticker)
    plt.legend()
    plt.show()
