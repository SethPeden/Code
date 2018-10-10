[xx, fs] = audioread('threevotes.wav');

ttSnippet = 0.25 : 1/ fs : 0.5;

xxSnippet = xx(round(0.25 * fs) : round(0.5 * fs));

plot(ttSnippet, xxSnippet);

xlabel('Time (s)');