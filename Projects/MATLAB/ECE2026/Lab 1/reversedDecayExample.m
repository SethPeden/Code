clear

[time, xDecay] = myDecayingSinusoid(10, 0.8, 2 * pi * 40, pi / 4, 8000, 0, 2);

xDecayReversed = xDecay(end : -1 : 1);

plot(time, xDecayReversed);