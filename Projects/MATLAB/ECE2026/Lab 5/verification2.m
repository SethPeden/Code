fs = 1000;
tStop = 5;
T = 1;
Amp = 1;

tt = 0 : 1 / fs : tStop;
xx = Amp * abs(sin(2 * pi * tt / T));

Tsect = 5;
Lsect = Tsect * fs;

spectrogram(xx, Lsect, [ ], [ ], fs, 'yaxis');

% plotspec(xx, fs, Lsect);