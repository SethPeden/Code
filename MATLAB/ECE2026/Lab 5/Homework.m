%% Recording and saving data
clear;
fs = 8000;
audio = audiorecorder(fs, 16, 1);
recordblocking(audio, 5);
xx = getaudiodata(audio);
save voice.mat audio xx fs

%% Analyzing
clear
voice = load('voice.mat');
soundsc(voice.xx, voice.fs);
spectrogram(voice.xx, 1024, [ ], [ ], voice.fs, 'yaxis');

%% Test
fs = 8000;
tt = 0 : 1 / fs : 5;
f0 = 115;
xx = 0 * tt;
for i = 1 : 10
    xx = xx + f0 * cos(2 * pi * i * f0 * tt);
end
soundsc(xx, fs);