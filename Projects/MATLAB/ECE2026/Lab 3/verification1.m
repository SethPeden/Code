clear

f1 = 410;
f2 = 470;
phi1 = 0;
phi2 = 0;

sigBeat.Amp = 10;
sigBeat.fc = 1 / 2 * (f2 - f1);
sigBeat.phic = 1 / 2 * (phi2 - phi1);
sigBeat.fDelt = 1 / 2 * (f2 + f1);
sigBeat.phiDelt = 1 / 2 * (phi2 + phi1);;
fs = 8000;
sigBeat.times = 0 : 1 / fs : 5;

sigBeatSum = sum2BeatStruct(sigBeat);

xx = sigBeatSum.values;

soundsc(xx, fs);

spectrogram(xx, [], [ ], [ ], fs, 'yaxis'); 
colorbar;