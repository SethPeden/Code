import sys

args = {}
i = 1
while i < len(sys.argv):
    args[sys.argv[i].replace('-', '')] = sys.argv[i + 1].replace('-', '')
    i += 2

option = args['intent'] if 'intent' in args.keys() else 'encrypt'
if option == 'encrypt':
    key = raw_input('Please enter a key for encryption: ')
else:
    key = raw_input('Please enter the key for decryption: ')
inFileName = args['input'] if 'input' in args.keys() else 'data.txt'
outFileName = args['output'] if 'output' in args.keys() else 'data.enc'

with open(inFileName, 'r') as inFile:
    data = list(map(lambda c: ord(c), inFile.read()))
    kb = list(map(lambda c: ord(c), key))
    enc = ''.join(list(map(lambda i: chr(data[i] ^ kb[i % len(kb)]), range(0, len(data)))))
    with open(outFileName, 'w') as outFile:
        outFile.write(enc)
