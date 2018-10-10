fs = 8000; % Sampling Frequency
audio = audiorecorder(fs, 16, 1); % Creating the Recording Object
recordblocking(audio, 3); % Recording Sound for 3 Seconds (?AHHH? Sound)

xx = getaudiodata(audio); % Grabbing the Audio Data for Plotting
tt = 0 : 1 / fs : (length(xx) - 1) / fs; % Defining the Time Range

tClipStart = 0.9; % Clipping Range Start
tClipEnd = 0.95; % Clipping Range End

ttClip = tt(round(tClipStart * fs) : round(tClipEnd * fs)); % Clipping the Time Domain
xxClip = xx(round(tClipStart * fs) : round(tClipEnd * fs)); % Clipping the Data Range

plot(ttClip, xxClip); % Plotting
title('T = 0.00866 s'); % Title