import sys

def average(a, b):
    return (a + b) / 2.0

def square_root(a, root = 2.0):
    b = a / root
    if (abs(root - b) < 1 / 10000000000000.0):
        return root
    return square_root(a, average(b, root))

if __name__ == '__main__':
    for i in range(1, len(sys.argv)):
        print('sqrt(' + sys.argv[i] + ') = ' + str(square_root(float(sys.argv[i]))))
else:
    pass
