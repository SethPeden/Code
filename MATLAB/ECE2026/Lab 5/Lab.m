%% 2.2
fSamp = 8000; %-Number of time samples per second
dt = 1 / fSamp;
tStart = 0;
tStop = 1.5;
tt = tStart : dt : tStop;
mu = 600;
fzero = 400;
phi = 2 * pi * rand; %-- random phase
%
psi = mu * tt .^ 2 + 2 * pi * fzero + phi; %% <=================== FILL IN THE CODE HERE
%
cc = real(7.7 * exp(1j * psi));
% soundsc( cc, fSamp ); %-- uncomment to hear the sound
plotspec(cc + 1j * 1e-12, fSamp, 256);
colorbar;
grid on; %-- with negative frequencies

