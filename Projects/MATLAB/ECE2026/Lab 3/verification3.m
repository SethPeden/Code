clear

c4 = 40;
keyNums = [c4];
steps = [2 2 1 2 2 2 1];

for i = steps 
    keyNums = [keyNums keyNums(end) + i];
end

amp = 10;
phase = 0;
fs = 8000;
tNote = 0 : 1 / fs : 0.4;
tSilence = 0 : 1 / fs : 0.1;
tTotal = [];
sound = [];

for i = keyNums
   sound = [sound, tSilence * 0, key2sinus(i, amp, 0, fs, tNote(end))];
   if (isempty(tTotal))
     tTotal = [tTotal, tSilence];
   else
     tTotal = [tTotal, tSilence + tTotal(end) + 1 / fs];
   end
   tTotal = [tTotal, tNote + tTotal(end) + 1 / fs];
end

sound = [sound, tSilence * 0];
tTotal = [tTotal, tSilence + tTotal(end) + 1 / fs];

soundsc(sound, fs);
subplot(211);
plot(tTotal, sound);
xlabel('Time (sec)');
ylabel('Notes');
title('C-Major Scale');
subplot(212);
spectrogram(sound, 1024, [ ], [ ], fs, 'yaxis'); 
colorbar;

% tTotal = 0 : 1 / fs : n
% where n = 8 * (0.1 + 0.5 + 2 * 1 / 8000) + 0.1 = 8 * (0.5 + 1 / 4000) + 0.1 
% = 4.0 + 0.002 + 0.1 = 4.102
% duration = 4.102 s