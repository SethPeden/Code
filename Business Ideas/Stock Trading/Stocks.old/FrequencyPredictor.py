import numpy as np
import matplotlib.pyplot as plt
from pandas_datareader import data as pdData
from datetime import datetime
from dateutil.relativedelta import relativedelta
import sys

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print 'Usage: python script.py <ticker>'
    else:
        ticker = sys.argv[1]
        stock_data = pdData.DataReader(ticker, 'yahoo', str(datetime.today() - relativedelta(years=10)).split(' ')[0], str(datetime.today()).split(' ')[0])['Close']
        price = np.array(stock_data)

        fft = np.fft.fft(price)

        thresh = np.mean(abs(fft))

        fft[abs(fft) < thresh] = 0

        pred = np.fft.ifft(fft)

        plt.figure(0)
        plt.plot(price, label='Price')
        plt.legend()

        plt.figure(1)
        plt.plot(abs(fft), label='FFT')
        plt.plot(thresh * np.ones((len(fft),)), label='FFT')
        plt.legend()

        plt.figure(2)
        plt.plot(pred, label='Prediction')
        plt.legend()

        plt.show()
