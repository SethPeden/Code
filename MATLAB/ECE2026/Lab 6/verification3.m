%% Verification 3
xpix = ones(256, 1) * cos(2 * pi * (0 : 255) / 32);
show_img(xpix); truesize;

%% Checking
T = 32;
B = 20;

xpix = ones(256, 1) * cos(2 * pi / T * (0 : B * T - 1));
show_img(xpix); truesize;