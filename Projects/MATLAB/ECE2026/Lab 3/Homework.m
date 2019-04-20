%% Beat Note

fs = 4000;
tt = 0 : 1 / fs : 4.04;

sigIn.Amp = 50;
sigIn.fDelt = 30;
sigIn.phiDelt = pi / 4;
sigIn.fc = 800;
sigIn.phic = 0;
sigIn.times = tt;

testingBeat = sum2BeatStruct(sigIn);

index = 8000 : 8300;

% subplot(121);
% plot(testingBeat.times(index), testingBeat.values(index));
% xlabel('Time (sec)');
% ylabel('y');
% title('Beat Note');

% subplot(122);
plotspec(testingBeat.values + j*1e-12, fs, 256);
colorbar;


%% Touch-Tone Dial 

Ts = 0.0002;
keysPressed = '268*073A';
% keysPressed = '3212333322223555321233332232111';
xx = DTMFdial(keysPressed, 1 / Ts);

soundsc(xx, 1 / Ts);
spectrogram(xx, 1024, [ ], [ ], 1 / Ts, 'yaxis'); 
colorbar;