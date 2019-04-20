fs = 8000;

tt = 0 : 1 / fs : 0.5;

freq = 1000 * (10 : 50);

for f = freq
    
    soundsc(cos(2 * pi * f * tt), fs);
    
    pause(tt(end));
    
end