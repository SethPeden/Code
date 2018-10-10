close all;
clear;
clc;

load echart;
m = 65; %% 65, 147, or 221
xx = echart(m, :);
bdiffh = [1 -1];
yy1 = conv(xx, bdiffh);

show_img(echart);

figure;
subplot(2, 1, 1);
stem(xx);

subplot(2, 1, 2);
stem(yy1);

startBlack = find(yy1 < 0);

startWhite = find(yy1 > 0);

bandWidths = startWhite - [0, startBlack(1 : end - 1)]; 
    % offset to align 
    % first black region with start of second white region 
    % (determining the width of black regions)

eWidth = bandWidths(2);
    % * 2 because our band is half the width