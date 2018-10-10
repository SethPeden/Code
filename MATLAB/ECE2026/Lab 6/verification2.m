fs = 4000;
tt = 0 : 1 / fs : 2;
A = 2;
fc = 800;
alp = 1000;
bet = 1.5;
gam = 0;

xx = A * cos(2 * pi * fc * tt + alp * cos(2 * pi * bet * tt + gam));

plotspec(xx + 1j * 1e-20, fs, 128);
soundsc(xx, fs);