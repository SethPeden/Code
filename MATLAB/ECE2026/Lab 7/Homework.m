close all;
clear;
clc;

%% A
image = imread('HP110v3.png');
[h, w] = size(image);
r = round(h / 2);
xn = double(image(r, :));

%% B
fdf = [1, -1];
yn = conv(xn, fdf);
subplot(121);
stem(xn);
title('xn');
subplot(122);
stem(yn);
title('yn');

%% C
figure;
threshold = 100;
dn = abs(yn) >= threshold;
ln = find(dn > 0);
subplot(121);
stem(ln);
title('ln');

%% D
deln = conv(ln, fdf);
deln = deln(2 : end - 1);
subplot(122);
stem(deln);
title('delta n');

%% E
% Based on the paragraph before 4.2.1, the UPC is comprised of three 
% delimiters - 2 (1-1-1) and 1 (1-1-1-1-1) - and then 12 digits that are 
% each 7 units in length. If we let theta1 = unit length, this gives us 
% that the total width should be 
% 2 * (3 * theta1) + 5 * (theta1) + 12 * (7 * theta1) = 95 * theta1.

%% 7
sublength = 59;
totalWidth = 95;
s = 0;
for i = 1 : length(deln) - sublength + 1
    subset = deln(i : i + sublength - 1);
    t = sum(subset) / totalWidth;
    s = s + t;
end
theta1 = s / i;
    
%% G
normDelN = round(deln / theta1);

%% H
oneIndices = find(normDelN == 1);
minIndex = 1;
for i = oneIndices
    if (any(i + 1 == oneIndices) && any(i + 2 == oneIndices))
        minIndex = i;
        break;
    end
end
maxIndex = length(normDelN);
for i = oneIndices(end : -1 : 1)
    if (any(i - 1 == oneIndices) && any(i - 2 == oneIndices))
        maxIndex = i;
        break;
    end
end
upc = normDelN(minIndex : maxIndex);

%% I
% Correct value should be 882780450165
decoded1 = decodeUPC(upc);

%% J
%% choose row 130
decoded2 = decode('OFFv3.png', 130);
