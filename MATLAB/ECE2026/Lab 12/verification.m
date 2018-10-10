%% Verification 1

hh = [1 -1];

ww = -pi : pi / 10000 : pi;

HH = freqz(hh, 1, ww);

plot(ww, abs(HH));
xlabel('w (rad)');
ylabel('|H|');
title('Frequency Response');

[signal, fs] = audioread('catsdogs.wav');

filteredsignal = conv(hh, signal);

figure;
subplot(211);
plotspec(signal, fs, 256);
xlabel('Time (s)');
ylabel('Frequency (Hz)');
title('Before Filtering');

subplot(212);
plotspec(filteredsignal, fs, 256);
xlabel('Time (s)');
ylabel('Frequency (Hz)');
title('After Filtering');

soundsc(signal, fs);

pause(length(signal) / fs);

soundsc(filteredsignal, fs);

%% Verification 2

f1 = 81;
f2 = 1031;
beta = 1.1;
fs = 8000;

tt = 0 : 1 / fs : 1.3;

b1 = beta + cos(2 * pi * f1 * tt);

bb = b1 .* cos(2 * pi * f2 * tt);

figure;
plot(tt, b1);
xlabel('Time (s)');
ylabel('Amplitude');
title('b1');

figure;
plot(tt, bb);
xlabel('Time (s)');
ylabel('Amplitude');
title('bb');

figure;
plot(tt, abs(bb));
xlabel('Time (s)');
ylabel('Amplitude');
title('|bb|');

figure;
plotspec(b1, fs, 512);
xlabel('Time (s)');
ylabel('Frequency (Hz)');
title('b1');

figure;
plotspec(bb, fs, 512);
xlabel('Time (s)');
ylabel('Frequency (Hz)');
title('bb');

figure;
plotspec(abs(bb), fs, 512);
xlabel('Time (s)');
ylabel('Frequency (Hz)');
title('|bb|');

%% Verification 3

load fc

filteredbb = filter(b, a, abs(bb));

tt2 = 0 : 1 / fs : (length(filteredbb) - 1)  / fs;

figure;
plot(tt2, filteredbb);
xlabel('Time (s)');
ylabel('Amplitude');
title('|bb| Through LPF');

figure;
plotspec(filteredbb, fs, 256);
xlabel('Time (s)');
ylabel('Frequency (Hz)');
title('|bb| Through LPF');
