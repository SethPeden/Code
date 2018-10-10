%% Setup
%--- make a plot of sum of cosines
dt = 1/800;
XX = rand(1,3).*exp(2i*pi*rand(1,3)); %--Random amplitude and phases
freq = 9;
ccsum = zeros(1,500);

%% Original
for kx = 1:length(XX)
    for kt = 1:500
        t = kt*dt;
        Ak = abs(XX(kx));
        phik = angle(XX(kx));
        ccsum(kt) = ccsum(kt) + Ak*cos(2*pi*freq*t + phik);
        tt(kt) = t;
    end
end
subplot(121);
plot(tt,ccsum) %-- Plot the sum sinusoid
title('Original');
xlabel('Time (s)');
ylabel('Y');
grid on, zoom on, shg

%% New
tt = (1:500) .* dt;
A = abs(XX);
phi = angle(XX);
complexAmp = sum(A .* exp(j * phi));
ccsum = abs(complexAmp) .* cos(2 * pi * freq * tt + angle(complexAmp));

subplot(122);
plot(tt,ccsum) %-- Plot the sum sinusoid
title('New');
xlabel('Time (s)');
ylabel('Y');
grid on, zoom on, shg