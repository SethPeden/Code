import numpy as np

class TSPredictor:

    def __init__(self, ref=5, pred=1):
        self.ref = ref
        self.pred = pred

    def train(self, observations):
        L = len(observations)
        observations = observations.reshape((L, ))

        rows = L - self.ref - self.pred + 1
        AColumns = self.ref
        aColumns = self.pred
        A = np.zeros((rows, AColumns))
        a = np.zeros((rows, aColumns))

        for r in np.arange(rows):
            A[r] = observations[r : r + self.ref]
            a[r] = observations[r + self.ref : r + self.ref + self.pred]

        self.weights, _, _, _ = np.linalg.lstsq(A, a, rcond=None)

        return self

    def predict(self, observations):
        L = len(observations)
        observations = observations.reshape((L, ))

        rows = L - self.ref - self.pred + 1
        AColumns = self.ref
        aColumns = self.pred
        A = np.zeros((rows, AColumns))

        for r in np.arange(rows):
            A[r] = observations[r : r + self.ref]

        a = np.matmul(A, self.weights)

        I = a.shape[0] + self.pred - 1
        pred = np.zeros((I, ))

        for i in np.arange(0, I):
            N = min(a.shape[0], i + 1) - max(0, i - self.pred + 1)
            for r in np.arange(max(0, i - self.pred + 1), min(a.shape[0], i + 1)):
                pred[i] += a[r][i - r] / N

        return pred
