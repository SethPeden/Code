L = 99;
bb = hamming(L)';

stem(bb);

ww = -pi : pi / 1000 : pi;
HH = freqz(bb, 1, ww);

figure;
subplot(211);
plot(ww, abs(HH));
xlabel('Frequency (w)');
ylabel('Magnitude');
title('|H|');

subplot(212);
plot(ww, angle(HH));
xlabel('Frequency (w)');
ylabel('Phase (rad)');
title('<H');

R = round(L / 4)