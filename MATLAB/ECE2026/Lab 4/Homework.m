%% 4.1
fs = 4000;
tt = 0 : 1 / fs : 2.6;
xx = 0 * tt;
starts = 0 : 0.25 : 1.5;
durs = [0.2, 0.2, 0.2, -1, -1, -1, -1];
steps = [0, 4, 3, 5, -5, -3,  -4];
key = 45;

for i = 1 : length(steps)
   key = key + steps(i);    
   start = starts(i);
   
   if (durs(i) > 0)
       dur = durs(i);
       note = key2sinus(key, 1, 0, fs, dur);
       startIndex = round(start * fs) + 1;       
       endIndex = startIndex + round(dur * fs);       
       xx(startIndex : endIndex) = xx(startIndex : endIndex) + note;       
   else       
       dur = tt(round(2.5 * fs)) - start;       
       note = key2sinus(key, 1, 0, fs, dur);       
       startIndex = round(start * fs) + 1;       
       endIndex = startIndex + round(dur * fs);       
       xx(startIndex: endIndex) = xx(startIndex: endIndex) + note;       
   end
end

soundsc(xx, fs);
spectrogram(xx, 256, [ ], [ ], fs, 'yaxis');
colorbar;

%% 4.2
sigFMexp.Amp = 7.7; %-- Amplitude
sigFMexp.fc = 395; %-- center frequency
sigFMexp.beta = 1.77; %-- FM parameter
sigFMexp.gamma = 5; %-- FM parameter
sigFMexp.t1 = 0; %-- starting time
sigFMexp.t2 = 3.04; %-- ending time

fs = 4000;

[xx, tt] = makeFMexpVals(sigFMexp, 1 / fs);

spectrogram(xx, 256, [ ], [ ], fs, 'yaxis');