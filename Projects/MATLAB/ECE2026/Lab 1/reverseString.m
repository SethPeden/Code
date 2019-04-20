function output = reverseString()
%reverseString Reverses the characters of a string and prints it out
%   'Mary had a little lamb' -> 'bmal elttil a dah yraM'

string = input('Please enter a string: ', 's');

output = string(end : -1 : 1);

end