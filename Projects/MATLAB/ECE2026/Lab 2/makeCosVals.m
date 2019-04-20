function sigOut = makeCosVals(sigIn, dur, tStart, dt)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

% sigOut.complexAmp = sigIn.complexAmp;
% sigOut.freq = sigIn.freq;
sigOut.times = tStart : dt : tStart + dur;
sigOut.values = abs(sigIn.complexAmp) * cos(2 * pi * sigIn.freq * sigOut.times + angle(sigIn.complexAmp));

end