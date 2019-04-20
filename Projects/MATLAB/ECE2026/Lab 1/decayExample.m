%%
% $10e^{-0.8t}cos(80\pi + \frac{\pi}{4})$

clear

tStart = 0;
tEnd = 2;
freq = 40;
samplingRate = 8000;
amp = 10;
phase = pi / 4;
b1 = 0.8;
b2 = 3;

[t1, x1] = myDecayingSinusoid(amp, b1, 2 * pi * freq, phase, samplingRate, tStart, tEnd);

[t2, x2] = myDecayingSinusoid(amp, b2, 2 * pi * freq, phase, samplingRate, tStart, tEnd);

% subplot(121);
plot(t1, x1);
title(['b = ' num2str(b1)]);
% subplot(122);
% plot(t2, x2);
% title(['b = ' num2str(b2)]);