%% A
Ts = 0.3e-3;
fs = 1 / Ts;

fc = 770;
df = 6;
freq = [697, fc - df, fc + df, 852];

dp = 0.02;
ds = 0.01;

c = firpmord(freq, [0, 1, 0], [ds, dp, ds], fs, 'cell');
mPredicted = c{1};
mActual = mPredicted - 11;

%% B
bb = firpm(mActual, c{2 : end});

%% C
ww = 0 : pi / 1000 : pi;
HH = freqz(bb, 1, ww);

ff = linspace(0, 1 / 2 * fs, length(ww));

plot(ff, abs(HH));
xlabel('Frequency (Hz)');
ylabel('|H|');
title('Frequency Response');
grid on;

%% D
dial = DTMFdial('159D*286A', fs);

figure;
plotspec(dial, fs, 256);
xlabel('Time (s)');
ylabel('Frequency (Hz)');
title('Before Filter #2');

filtered = conv(dial, bb);

figure;
plotspec(filtered, fs, 256);
xlabel('Time (s)');
ylabel('Frequency (Hz)');
title('After Filter #2');