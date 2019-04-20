fs = 32000;
t = 0 : 1 / fs : 1;
f = 440;
x = cos(2 * pi * f * t);

ft = fft(x);
ftp = ft;
% for i = 1 : 2 : length(ftp)
%     ftp(i) = ftp(i);
% end

H = abs(ftp);
plot(H);

z = ifft(ftp);
soundsc(z, fs);