%% A
wd2 = 2 * pi * 2 / 32; 
xpix2 = ones(256, 1) * cos(wd2 * (0 : 255));
show_img(xpix2);

wd14 = 2 * pi * 14 / 32; 
xpix14 = ones(256, 1) * cos(wd14 * (0 : 255));
show_img(xpix14);

%% B
show_img(xpix2);

show_img(xpix14);

show_img(xpix2(1 : 2 : end, 1 : 2 : end));

show_img(xpix14(1 : 2 : end, 1 : 2 : end));