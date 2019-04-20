import numpy as np

# Class definition of a Linear Time Series Predictor
class LTSPredictor:

    # Initializer of a Linear Time Series Predictor
    # @param predictions : number of future values to predict
    # @param reflection : number of past values to use for prediction
    def __init__(self, predictions, reflection):
        self.predictions = predictions
        self.reflection = reflection

    # Function to train the Linear Time Series Predictor
    # @param observations : past values with which to train the Linear Time Series Predictor
    def train(self, observations):
        L = len(observations)
        observations = np.reshape(observations, (L,))

        D = L - (self.predictions + self.reflection) + 1
        if D < 1:
            raise Exception('Not enough Observations for a Linear Time Series Prediction.')

        O = np.zeros((D, self.reflection))
        for row in np.arange(0, D):
            O[row] = observations[row : row + self.reflection]

        o = np.zeros((D, self.predictions))
        for row in np.arange(0, D):
            o[row] = observations[row + self.reflection : row + self.reflection + self.predictions]

        self.coefficients, _, _, _ = np.linalg.lstsq(O, o, rcond=None)

    # Function to get multiple LTSM predictions with the Linear Time Series Predictor
    # @param observations : past values with which to predict with a Linear Time Series Predictor
    #                       - If the length of @param observations is longer than
    #                         self.relfection, then multiple predictions will be made
    def getPredictions(self, observations):
        L = len(observations)
        observations = np.reshape(observations, (L,))

        z = np.zeros((max(self.reflection - L, 0),))
        observations = np.hstack((z, observations))

        D = L - self.reflection + 1

        O = np.zeros((D, self.reflection))
        for row in np.arange(0, D):
            O[row] = observations[row : row + self.reflection]

        return np.matmul(O, self.coefficients)

    # Function to predict with the Linear Time Series Predictor
    # @param observations : past values with which to predict with a Linear Time Series Predictor
    #                       - If the length of @param observations is longer than
    #                         self.relfection, then multiple predictions will be made
    def predict(self, observations):
        predictions = self.getPredictions(observations)

        rows, columns = predictions.shape

        sum = np.zeros((rows + self.predictions - 1,))

        for i in np.arange(0, rows + self.predictions - 1):
            N = min(i + 1, rows) - max(i - self.predictions + 1, 0)
            for r in np.arange(max(i - self.predictions + 1, 0), min(i + 1, rows)):
                sum[i] += predictions[r, i - r] / N

        return sum
