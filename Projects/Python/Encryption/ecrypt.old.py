import sys

args = {}
for i in range(1, len(sys.argv)):
    arg = sys.argv[i].split('=')
    args[arg[0]] = arg[1]

input = args['input'] if 'input' in args.keys() else 'data.txt'
output = args['output'] if 'output' in args.keys() else 'data.enc'
key = args['key'] if 'key' in args.keys() else '!!!ThisIsVeryUnsafe!!!'

with open(input, 'r') as inFile:
    data = list(map(lambda c: ord(c), inFile.read()))
    kb = list(map(lambda c: ord(c), key))
    enc = ''.join(list(map(lambda i: chr(data[i] ^ kb[i % len(kb)]), range(0, len(data)))))
    with open(output, 'w') as outFile:
        outFile.write(enc)
