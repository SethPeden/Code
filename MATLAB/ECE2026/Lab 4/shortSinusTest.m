amps = [100, 120];
freqs = [800,2000];
phases = [0.6*pi, -0.1*pi];
fs = 8000;
tStart = [0.1, 0.1];
durs = [0.4,0.4];
maxTime = max(tStart+durs) + 0.1; %-- Add time to show signal ending
durLengthEstimate = ceil(maxTime*fs);
tt = (0:durLengthEstimate)*(1/fs); %-- be conservative (add one)
xx = 0*tt; %--make a vector of zeros to hold the total signal
for kk = 1:length(amps)
    nStart = round(tStart(kk) * fs)+1; %-- add one to avoid zero index
    xNew = shortSinus(amps(kk), freqs(kk), phases(kk), fs, durs(kk));
    Lnew = length(xNew);
    nStop = nStart + Lnew - 1; %<========= Add code
    xx(nStart:nStop) = xx(nStart:nStop) + xNew;
end
spectrogram(xx, 1024, [], [], fs, 'yaxis');
colorbar;

soundsc(xx, fs);

% plotspec(xx,fs,256); grid on