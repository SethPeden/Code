myLFMsig.f1 = 200;
myLFMsig.t1 = 0; 
myLFMsig.t2 = 1.5;
myLFMsig.slope = 1800;
myLFMsig.complexAmp = 10*exp(1j * 0.3 * pi);
dt = 1 / 8000; % 8000 samples per sec i
outLFMsig = makeLFMvals(myLFMsig,dt);

plot(outLFMsig.times, outLFMsig.values);
plotspec(outLFMsig.values + 1j * 1e-14, 1 / dt, 256);
soundsc(outLFMsig.values, 1 / dt);