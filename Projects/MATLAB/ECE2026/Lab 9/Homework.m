%% A
wp = 0.60 * pi;
ws = 0.64 * pi;
dp = 0.05;
ds = 0.01;
fs = 10000;

freqs = [wp, ws] * fs / (2 * pi);

% Doesn't meet specifications
c = firpmord(freqs, [1, 0], [dp, ds], fs, 'cell');
m = c{1};
bb = firpm(m, c{2 : end});

%% B
plot(bb);
xlabel('n');
title('Impulse Response')

%% C
ww = -pi : pi / 5000 : pi;

% Doesn't meet specifications
% Turn in zoomed plots to show how specifications aren't met 
HH = freqz(bb, 1, ww);
figure;
plot(ww, abs(HH));
grid on;
xlabel('\omega (rad)');
ylabel('|H|');
title('Frequency Response (Does Not Meet Specifications)');

% hold on;
% plot([wp, wp], [0, 1.2]);
% plot([ws, ws], [0, 1.2]);
% hold off;

%% D
c = firpmord(freqs, [1, 0], [dp, ds], fs, 'cell');
% Altering order to meet specifications
mNew = c{1} + 2;
bbNew = firpm(mNew, c{2 : end});

% Does meet specifications
% Turn in zoomed plots to show how specifications are met 
HHNew = freqz(bbNew, 1, ww);
figure;
plot(ww, abs(HHNew));
grid on;
xlabel('\omega (rad)');
ylabel('|H|');
title('Frequency Response (Does Meet Specifications)');

% hold on;
% plot([wp, wp], [0, 1.2]);
% plot([ws, ws], [0, 1.2]);
% hold off;

%% E
figure;
plot(ww, angle(HHNew));
xlabel('\omega (rad)');
ylabel('<H (rad)');
title('Phase');

% Determining the slope
dPhase = diff(angle(HHNew)) ./ diff(ww);
slope = mode(dPhase);