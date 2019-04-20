%% 4.1
lighthouse = imread('lighthouse.png');

show_img(lighthouse);
truesize;
title('Before Down-Sampling');

show_img(lighthouse(1 : 2 : end, 1 : 2 : end));
truesize;
title('After Down-Sampling');

%% 4.2
picture = imread('GrayscaleChoice.png');
picture = picture(:, :, 1);

show_img(picture);
truesize;
title('Before Down-Sampling');

show_img(picture(1 : 3 : end, 1 : 3 : end));
truesize;
title('After Down-Sampling');