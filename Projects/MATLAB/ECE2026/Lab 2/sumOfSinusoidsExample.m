ss(1).freq = 15;
ss(1).complexAmp = exp(j*pi/4);
ss(2).freq = 12;
ss(2).complexAmp = 2i;
ss(3).freq = 9;
ss(3).complexAmp = -4;
%
dur = 1;
tstart = -0.5;
dt = 1/(15*32); %-- use the highest frequency to define delta_t
%
ssOut = addCosVals(ss, dur, tstart, dt);

plot(ssOut.times, ssOut.values);

%% Description
% T = 0.05833 s - -0.275 s = 0.33333 s.
% The Period measured here is is related to the fundamental frequency (f) by T = 1 / f.
% f = 3 Hz because it is the Greatest Common Factor
% of the frequencies that are combined to create the larger sinusoid.