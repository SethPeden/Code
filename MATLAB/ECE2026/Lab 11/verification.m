%% Verification 3

dur = 15;

[ecgsig, fs, fint] = ECGmakeSig15('speden3', dur);

theta = 2 * pi * fint / fs;
r = 0.95;
num = poly([exp(j * theta), exp(-j * theta)]);
den = poly([r * exp(j * theta), r * exp(-j * theta)]);

hn = filter(num, den, [1, zeros(1, 50)]);
ww = 0 : pi / 10000 : pi;
ff = linspace(0, 1 / 2 * fs, length(ww));
HH = freqz(hn, 1, ww);
plot(ff, abs(HH));
xlabel('Frequency (Hz)');
ylabel('|H|');
title('Frequency Response');

%% Verification 5

tt = 0 : 1 / fs : dur;
tt = tt(1 : end - 1);

filteredecgsig = filter(num, den, ecgsig);

figure;
subplot(211);
plot(tt, ecgsig');
xlabel('Time (s)');
ylabel('Amplitude');
title('Unfiltered ECG Signal');

subplot(212);
plot(tt, filteredecgsig');
xlabel('Time (s)');
ylabel('Amplitude');
title('Filtered ECG Signal');

%% Verification 6

figure;
subplot(211);
plotspec(ecgsig, fs, 256);
xlabel('Time (s)');
ylabel('Frequency (Hz)');
title('Unfiltered ECG Signal');

subplot(212);
plotspec(filteredecgsig, fs, 256);
xlabel('Time (s)');
ylabel('Frequency (Hz)');
title('Filtered ECG Signal');