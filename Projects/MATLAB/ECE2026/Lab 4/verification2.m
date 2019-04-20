fs = 4000;

t1 = 0.6 : 1 / fs : 0.6 + 0.5;
s1 = cos(2 * pi * 1200 * t1);

t2 = 0.2 : 1 / fs : 0.2 + 1.6;
s2 = cos(2 * pi * 750 * t2);

resultStart = round(min(t1(1) * fs, t2(1) * fs));
resultEnd = round(max(t1(end) * fs, t2(end) * fs));

tt = 0 : 1 / fs : resultEnd / fs;
xx = 0 * tt;

sumStart = round(max(t1(1) * fs, t2(1) * fs));
sumEnd = round(min(t1(end) * fs, t2(end) * fs));

% Before Addition
if (sumStart / fs == t1(1))
    
    % t2 starts first
    xx(resultStart : resultStart + sumStart - 1) = s2(1 : sumStart);
    
    % Addition
    xx(sumStart : sumEnd) = s1(1 : sumEnd - sumStart + 1) + s2(sumStart : sumEnd);
    
else
    
    % t1 starts first
    xx(resultStart : resultStart + sumStart - 1) = s1(1 : sumStart);
    
    % Addition
    xx(sumStart : sumEnd) = s2(1 : sumEnd - sumStart) + s1(sumStart : sumEnd);
    
end
    
% After Addition
if (sumEnd / fs == t1(end))
    
    % t1 ends first
    xx(sumEnd + 1 : end) = s2(sumEnd + 1 - resultStart : end);
    
else
    
    % t2 ends first
    xx(sumEnd + 1 : end) = s1(sumEnd + 1 - resultStart : end);
    
end

spectrogram(xx, 256, [], [], fs, 'yaxis');