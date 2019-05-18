from TSPrediction import TSPredictor
import numpy as np
import matplotlib.pyplot as plt
from pandas_datareader import data as pdData
from datetime import datetime
from dateutil.relativedelta import relativedelta
import sys
import json

tickers = { 'AAPL', 'MSFT', 'GOOG', 'SNAP', 'FB', 'TSLA', 'F', 'GM', 'FCAU', 'DGAZ', 'UGAZ' }

if __name__ == '__main__':

    # Training
    training = []
    for ticker in tickers:
        stock = pdData.DataReader(ticker, 'yahoo', str(datetime.today() - relativedelta(months=4)).split(' ')[0], str(datetime.today() - relativedelta(months=1)).split(' ')[0])
        close = stock['Close'] / stock['Close'][0]
        training = np.append(training, np.array(close))

    predictor = TSPredictor().train(training)
    n = np.arange(len(training))
    prediction = predictor.predict(training)
    m = np.arange(len(prediction)) + predictor.ref

    plt.plot(n, training, label='Training')
    plt.plot(m, prediction, label='Prediction')
    plt.legend()
    plt.show()

    # Validation
    for ticker in tickers:
        stock = pdData.DataReader(ticker, 'yahoo', str(datetime.today() - relativedelta(months=1)).split(' ')[0], str(datetime.today() - relativedelta(months=0)).split(' ')[0])
        close = np.array(stock['Close'])
        n = np.arange(len(close))
        prediction = predictor.predict(close)
        m = np.arange(len(prediction)) + predictor.ref
        plt.plot(n, close, label='Closing Price')
        plt.plot(m, prediction, label=ticker + ' Prediction')
        plt.title(ticker)
        plt.legend()
        plt.show()
