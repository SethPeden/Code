function decoded = decode(i, row)

%% A
image = imread(i);
[h, w] = size(image);
if (~isempty(row))
    r = row;
else
    r = round(h / 2);
end
xn = double(image(r, :));

%% B
fdf = [1, -1];
yn = conv(xn, fdf);

%% C
threshhold = 100;
dn = abs(yn) >= threshhold;
ln = find(dn > 0);

%% D
deln = conv(ln, fdf);
deln = deln(2 : end - 1);

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
decoded = decodeUPC(upc);

end