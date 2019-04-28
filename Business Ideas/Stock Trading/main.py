from TSPrediction import TSPredictor
import numpy as np
import matplotlib.pyplot as plt
from pandas_datareader import data as pdData
from datetime import datetime
from dateutil.relativedelta import relativedelta
import sys

def shouldBuy(observations):
    L = len(observations)
    observations = observations.reshape((L, ))
    predictor = TSPredictor(25, 10).train(observations)
    prediction = predictor.predict(observations)
    future = prediction[-predictor.pred:]
    return np.mean(np.diff(future)) > 0

if __name__ == '__main__':
    for i in np.arange(1, len(sys.argv)):
        ticker = sys.argv[i]

        trainDataFrame = pdData.DataReader(ticker, 'yahoo', str(datetime.today() - relativedelta(months=48)).split(' ')[0], str(datetime.today() - relativedelta(months=12)).split(' ')[0])['Close']
        trainDates = trainDataFrame.keys()
        trainClose = np.array(trainDataFrame)

        predictor = TSPredictor(25, 10).train(trainClose)
        trainPredictionClose = predictor.predict(trainClose)
        trainPredictionDates = (trainDates.to_pydatetime() + relativedelta(days=predictor.pred))[-len(trainPredictionClose): ]

        testDataFrame = pdData.DataReader(ticker, 'yahoo', str(datetime.today() - relativedelta(months=12)).split(' ')[0], str(datetime.today()).split(' ')[0])['Close']
        testDates = testDataFrame.keys()
        testClose = np.array(testDataFrame)

        testPredictionClose = predictor.predict(testClose)
        testPredictionDates = (testDates.to_pydatetime() + relativedelta(days=predictor.pred))[-len(testPredictionClose): ]

        print ticker , ': ', ('Buy!' if shouldBuy(testPredictionClose) else 'Sell!')

        plt.plot(trainDates, trainClose, label='Train Close')
        plt.plot(testDates, testClose, label='Test Close')
        plt.plot(trainPredictionDates, trainPredictionClose, label='Train Prediction')
        plt.plot(testPredictionDates, testPredictionClose, label='Test Prediction')
        plt.legend()
        plt.title(ticker)
        plt.show()
