%% A
clear;
fs = 1000;
tStop = 5;
T = 1;
Amp = 1;

tt = 0 : 1 / fs : tStop;
xx = Amp * abs(sin(2 * pi * tt / T));

Tsect = 5 * T;
Lsect = Tsect * fs;

plotspecDB(xx, fs, Lsect, 80);

%% B
clear;
fs = 1000;
tStop = 5;
T = 2;
Amp = 1;

tt = 0 : 1 / fs : tStop;
xx = Amp * abs(sin(2 * pi * tt / T));

Tsect = 2 * T;
Lsect = Tsect * fs;

plotspecDB(xx, fs, Lsect, 80);