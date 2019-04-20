clear;

%% Make Time Vector
tt = 0 : 120;

%% Make Distance Vector
dd = 2 * tt;

%% Make Noise
noise = 1 + 2 .* randn(size(dd));

%% Add Noise
ddNoisy = dd + noise;

%% Plotting
subplot(311);
plot(tt, dd);
xlabel('Time (s)');
ylabel('Distance Travelled (m)');
title('Tracking Distance');

hold on;

plot(tt, ddNoisy, 'r--');
legend('Perfect', 'Noisy', 'Location', 'southeast');
hold off;

%% Zooming
ttShort = tt(1 : 11);
ddShort = dd(1 : length(ttShort));
ddNoisyShort = ddNoisy(1 : length(ttShort));

subplot(312);
plot(ttShort, ddShort, 'b-', ttShort, ddNoisyShort, 'r--');
xlabel('Time (s)');
ylabel('Distance Travelled (m)');
title('Zoom Option 1');
legend('Perfect', 'Noisy', 'Location', 'southeast');

subplot(313);
plot(tt, dd, 'b-', tt, ddNoisy, 'r--');
xlabel('Time (s)');
ylabel('Distance Travelled (m)');
title('Zoom Option 2');
legend('Perfect', 'Noisy', 'Location', 'southeast');
xlim([0 length(ttShort)]);

