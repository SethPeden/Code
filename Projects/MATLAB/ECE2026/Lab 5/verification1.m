fSamp = 4000; %-Number of time samples per second
dt = 1 / fSamp;
tStart = 0;
tStop = 5;
tt = tStart : dt : tStop;
mu = (11400 - 900) / (5 * 2);
fzero = 900;
phi = 2 * pi * rand; %-- random phase
%
psi = 2 * pi * (mu * tt .^ 2 + fzero .* tt) + phi; %% <=================== FILL IN THE CODE HERE
%
cc = real(7.7 * exp(1j * psi));
soundsc(cc, fSamp); %-- uncomment to hear the sound
plotspec(cc + 1j * 1e-12, fSamp, 128);
colorbar;
grid on; %-- with negative frequencies