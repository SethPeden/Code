function [tt, xs] = myDecayingSinusoid(A, b, omega, phi, fs, tStart, tEnd)
%myDecayingSinusoid(A, b, omega, phi, fs, tStart, tEnd) ->
%Ae^(-bt)cos(omega * t + phi)
%   Returns an array of values for the above function

tt = tStart : 1 / fs : tEnd; % time indices

xs = A .* exp(-b .* tt) .* cos(omega * tt + phi);

end