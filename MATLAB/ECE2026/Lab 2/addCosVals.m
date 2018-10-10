function sigOut = addCosVals(cosIn, dur, tstart, dt)
%ADDCOSVALS Synthesize a signal from sum of sinusoids
% (do not assume all the frequencies are the same)
%
% usage: sigOut = addCosVals(cosIn, dur, tstart, dt)
%
% cosIn = vector of structures; each one has the following fields:
% cosIn.freq = frequency (in Hz), usually none should be negative
% cosIn.complexAmp = COMPLEX amplitude of the cosine
%
% dur = total time duration of all the cosines
% start = starting time of all the cosines
% dt = time increment for the time vector
% The output structure has only signal values because it is not necessarily a sinusoid
% sigOut.values = vector of signal values at t = sigOut.times
% sigOut.times = vector of times, for the time axis
%
% The sigOut.times vector should be generated with a small time increment that
% creates 32 samples for the shortest period, i.e., use the period
% corresponding to the highest frequency cosine in the input array of structures.

sigOut.times = tstart : dt : tstart + dur;
sigOut.values = zeros(1, length(sigOut.times));
for c = cosIn
    sigOut.values = sigOut.values + abs(c.complexAmp) * cos(2 * pi * c.freq * sigOut.times + angle(c.complexAmp));   
end
end