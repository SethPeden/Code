close all
clear all
num_sinusoid = [1 3 10 50];
f0 = 1; %fundamental freq = 1 Hz
for jj = 1 : length(num_sinusoid)
    clear cosIn
    for kk = 1:num_sinusoid(jj) %calculate the freq and amp of each harmonic
        cosIn(kk).freq = kk * f0;
        cosIn(kk).complexAmp = (1 - (-1) ^ kk) / pi / kk * exp(1j / 2 * pi);
    end
    dur = 3;
    dt = 0.05;
    tstart = 0;
    a(jj) = addCosVals(cosIn, dur, tstart, dt);
    subplot(2, 2, jj)
    plot(a(jj).times, a(jj).values)
    title(sprintf('Sum of %d sinusoids', num_sinusoid(jj)))
end

%% Question 2
close all
clear all
num_sinusoid = 50;
f0 = 2; %fundamental freq = 2 Hz
dur = 3;
dt = 0.001;
tstart = 0;
clear cosIn
for kk = 1 : num_sinusoid %calculate the freq and amp of each harmonic
    cosIn(kk).freq = kk * f0;
    cosIn(kk).complexAmp = (1 - (-1) ^ kk) / pi / kk * exp(1j / 2 * pi)
end
a = addCosVals(cosIn, dur, tstart, dt);
plot(a.times, a.values);
axis([-inf, inf, -1, 1]);
title(sprintf('Sum of %d sinusoids', num_sinusoid))

%% Question 3
close all
clear all
num_sinusoid = 10;
f0 = 1; %fundamental freq = 1 Hz
dur = 3;
dt = 0.01;
tstart = 0;
clear cosIn
for kk = 1 : num_sinusoid %calculate the freq and amp of each harmonic
    cosIn(kk).freq = kk * f0;
    cosIn(kk).complexAmp = (1 - (-1) ^ kk) / pi / kk * exp(1j / 2 * pi)
end
a = addCosVals(cosIn, dur, tstart, dt);
a.values = a.values + 0.5;
plot(a.times, a.values);
axis([-inf, inf, -0.5, 1.5]);
title(sprintf('Sum of %d sinusoids', num_sinusoid))