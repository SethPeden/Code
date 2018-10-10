function xx = DTMFdial(keyNames, fs)
%DTMFDIAL Create a signal vector of tones that will dial
% a DTMF (Touch Tone) telephone system.
%
% usage: xx = DTMFdial(keyNames,fs)
% keyNames = vector of CHARACTERS containing valid key names
% fs = sampling frequency (1/Ts)
% xx = signal vector that is the concatenation of DTMF tones.
%
TTkeys = ['1', '2', '3', 'A';
          '4', '5', '6', 'B';
          '7', '8', '9', 'C';
          '*', '0', '#', 'D'];
      
for k = keyNames
   if (sum(sum((TTkeys == k))) == 0)
       error(['''', k, '''', ' is not a valid key.']);
   end
end
      
TTcolTones = [1209, 1336, 1477, 1633]; %-- in Hz
TTrowTones = [697, 770, 852, 941];
numKeys = length(keyNames);
durDualTone = 0 : 1 / fs : .180; %-- in seconds
LenDualTone = length(durDualTone);
durSilence = 0 : 1 / fs : .048;
LenSilence = length(durSilence);
xx = zeros(1, numKeys * (LenDualTone + LenSilence)); %- initialize xx to be long enough to hold the entire output
n1 = 1;
for kk = 1 : numKeys
    [jrow,jcol] = find(keyNames(kk) == TTkeys); %- which key?
    % more code to make the dual-tone signals
    % precede each dual-tone signal with a short interval of silence
    freqs = [TTrowTones(jrow), TTcolTones(jcol)];
    xx(n1 : n1 + LenDualTone - 1) = cos(2 * pi * freqs(1) * durDualTone) + cos(2 * pi * freqs(2) * durDualTone);
    n1 = n1 + LenDualTone;
    xx(n1 : n1 + LenSilence - 1) = 0 * durSilence;
    n1 = n1 + LenSilence;
end