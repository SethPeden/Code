import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.preprocessing import MinMaxScaler
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import LSTM
from keras.layers import Dropout

class MLPredictor:

    @staticmethod
    def load(file='', predictions=-1, reflection=-1):
        if file == '':
            file = './P{}R{}_model.h5'.format(predictions, reflection)
        self.regressor = keras.models.load_model(file)

    def __init__(self, predictions, reflection):
        self.predictions = predictions
        self.reflection = reflection
        self.sc = MinMaxScaler(feature_range=(0, 1))

    def createModel(self, input_shape):
        self.regressor = Sequential()
        self.regressor.add(LSTM(units = 50, return_sequences = True, input_shape = (input_shape, 1)))
        self.regressor.add(Dropout(0.2))
        self.regressor.add(LSTM(units = 50, return_sequences = True))
        self.regressor.add(Dropout(0.2))
        self.regressor.add(LSTM(units = 50, return_sequences = True))
        self.regressor.add(Dropout(0.2))
        self.regressor.add(LSTM(units = 50))
        self.regressor.add(Dropout(0.2))
        self.regressor.add(Dense(units = self.predictions))
        self.regressor.compile(optimizer = 'adam', loss = 'mean_squared_error')

    def save(self, file=''):
        if file == '':
            file = './P{}R{}_model.h5'.format(self.predictions, self.reflection)
        self.regressor.save(file)

    def train(self, observations, epochs=100, batch_size=32):
        R = observations.shape[0]
        C = observations.shape[1]

        if C == None:
            R = 1

        x_train = np.array([])
        y_train = np.array([])

        for r in np.arange(0, R):
            observation = observations[r] if R > 1 else observations
            L = len(observation)

            D = L - (self.predictions + self.reflection) + 1
            if D < 1:
                raise Exception('Not enough Observations for a Linear Time Series Prediction.')

            x = np.zeros((D, self.reflection))
            for row in np.arange(0, D):
                x[row] = observation[row : row + self.reflection]

            y = np.zeros((D, self.predictions))
            for row in np.arange(0, D):
                y[row] = observation[row + self.reflection : row + self.reflection + self.predictions]

            if len(x_train) == 0:
                x_train = x
                y_train = y
            else:
                x_train = np.vstack((x_train, x))
                y_train = np.vstack((y_train, y))

        x_train = self.sc.fit_transform(x_train)
        y_train = self.sc.fit_transform(y_train)

        x_train = np.reshape(x_train, (x_train.shape[0], x_train.shape[1], 1))

        self.createModel(x_train.shape[1])
        self.regressor.fit(x_train, y_train, epochs=epochs, batch_size=batch_size)

    def predict(self, observations):
        R = observations.shape[0]
        C = observations.shape[1] if len(observations) != R else None

        if C == None:
            R = 1

        observations = observations.reshape(-1, 1)
        observations = self.sc.fit_transform(observations)

        x_test = np.array([])

        for r in np.arange(0, R):
            observation = observations[r] if R > 1 else observations
            L = len(observation)

            D = L - (self.predictions + self.reflection) + 1
            if D < 1:
                raise Exception('Not enough Observations for a Linear Time Series Prediction.')

            x = np.zeros((D, self.reflection))
            for row in np.arange(0, D):
                x[row] = observation[row : row + self.reflection].reshape((self.reflection,))

            if len(x_test) == 0:
                x_test = x
            else:
                x_test = np.vstack((x_test, x))

        x_test = np.reshape(x_test, (x_test.shape[0], x_test.shape[1], 1))

        prediction = self.regressor.predict(x_test)
        return self.sc.inverse_transform(prediction)
