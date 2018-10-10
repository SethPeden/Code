%% A
load speechbad.mat

sound(xxbad, fs);

plotspecDB(xxbad, fs, 256);
xlabel('Time (s)');
ylabel('Frequency (Hz)');
title('Before Nulling');

%% B
n1 = [1, -2 * cos(2 * pi * f_interference(1) / fs), 1];

n2 = [1, -2 * cos(2 * pi * f_interference(2) / fs), 1];

nn = conv(n1, n2);

%% C
ww = -pi : pi / 100 : pi;

H = freqz(nn, 1, ww);

figure;
subplot(211);
plot(ww, abs(H));
xlabel('\omega (rad)');
ylabel('Magnitude');
title('|H|');
subplot(212);
plot(ww, angle(H));
xlabel('\omega (rad)');
ylabel('Phase (rad)');
title('<H');

%% D
xxgood = conv(xxbad, nn);

figure;
plotspecDB(xxbad, fs, 256);
xlabel('Time (s)');
ylabel('Frequency (Hz)');
title('Before Nulling');

figure;
plotspecDB(xxgood, fs, 256);
xlabel('Time (s)');
ylabel('Frequency (Hz)');
title('After Nulling');
sound(xxgood, fs);
