#include <iostream>
#include <fstream>
#include "Array.h"
#include "Stack.h"
using namespace std;

typedef unsigned char byte;

Array<string> getEncodings() {
	Array<string> encodings;
	string in;
	fstream file;
	file.open("Encoding.txt");
	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, in);
			encodings += { in };
		}
		file.close();
	} else {
		cout << "Error opening Encoding.txt" << endl;
	}
	return encodings;
}

void loadInt(string val, Array<byte> &instructions) {
	int i = stoi(val, nullptr, 10);
	instructions += { byte(i >> 24), byte(i >> 16), byte(i >> 8), byte(i) };
}

Array<byte> loadFile(string fileName) {

	static Array<string> encodings;
	if (!encodings.size())
		encodings = getEncodings();

	Array<byte> instructions;

	string in;
	fstream file;
	file.open(fileName);
	if (file.is_open()) {

		while (!file.eof()) {

			getline(file, in);
			int brk = min(in.find(" "), in.find("\t"));
			string inst = in.substr(0, brk);
			string val = brk < in.size() ? in.substr(brk) : "";

			for (int i = 0; i < encodings.size(); i++) {

				string instComp = encodings[i].substr(0, encodings[i].find(":"));
				if (inst == instComp) {

					int func = stoi(encodings[i].substr(encodings[i].find(":") + 1), nullptr, 10);
					instructions += { byte(func) };

					// Only use this switch if the instruction has arguments.
					switch (func) {
						case 0: {
							loadInt(val, instructions);
							break;
						}
						case 8: {
							loadInt(val, instructions);
							break;
						}
						case 9: {
							loadInt(val, instructions);
							break;
						}
						case 10: {
							loadInt(val, instructions);
							break;
						}
						case 13: {
							loadInt(val, instructions);
							break;
						}
						case 14: {
							loadInt(val, instructions);
							break;
						}
						default:
							break;
					}

				}

			}

		}

		file.close();

	}

	return instructions;

}

void showStackState(Stack<byte> copy) {

	cout << "Stack State: [ ";
	while (copy.size() > 1)
		cout << hex << int(copy.pop()) << ", ";
	if (copy.size() > 0)
		cout << hex << int(copy.pop()) << " ";
	cout << "]" << endl;

}

int grabInt(Stack<byte> &data) {
	int temp = 0;
	for (int i = 0; i < 4; i++)
		temp |= ((data.pop() & 0xFF) << (8 * i));
	return temp;
}

void pushInt(Array<byte> &instructions, int &PC, Stack<byte> &data) {
	for (int i = 0; i < 4; i++)
		data.push(instructions[++PC]);
}

int run(Array<byte> instructions, Stack<byte> data) {

	int PC = 0;

	while (PC < instructions.size()) {

		switch (instructions[PC]) {
			case 0: {
				pushInt(instructions, PC, data);
				break;
			}
			case 1: {
				int args[2];
				for (int j = 0; j < 2; j++)
					args[j] = grabInt(data);
				args[0] += args[1];
				for (int i = 3; i >= 0; i--)
					data.push(args[0] >> (8 * i));
				break;
			}
			case 2: {
				int args[2];
				for (int j = 0; j < 2; j++)
					args[j] = grabInt(data);
				args[0] -= args[1];
				for (int i = 3; i >= 0; i--)
					data.push(args[0] >> (8 * i));
				break;
			}
			case 3: {
				int args[2];
				for (int j = 0; j < 2; j++)
					args[j] = grabInt(data);
				args[0] *= args[1];
				for (int i = 3; i >= 0; i--)
					data.push(args[0] >> (8 * i));
				break;
			}
			case 4: {
				int args[2];
				for (int j = 0; j < 2; j++)
					args[j] = grabInt(data);
				args[0] /= args[1];
				for (int i = 3; i >= 0; i--)
					data.push(args[0] >> (8 * i));
				break;
			}
			case 5: {
				int args[2];
				for (int j = 0; j < 2; j++)
					args[j] = grabInt(data);
				args[0] %= args[1];
				for (int i = 3; i >= 0; i--)
					data.push(args[0] >> (8 * i));
				break;
			}
			case 6: {
				int args[2];
				for (int j = 0; j < 2; j++)
					args[j] = grabInt(data);
				for (int i = 1; i < args[1]; i++)
					args[0] *= args[1];
				for (int i = 3; i >= 0; i--)
					data.push(args[0] >> (8 * i));
				break;
			}
			case 7: {
				cout << dec << grabInt(data) << endl;
				break;
			}
			case 8:	{
				pushInt(instructions, PC, data);
				int limit = min(grabInt(data), data.size());
				Array<byte> bytes;
				for (int i = 0; i < limit; i++)
					bytes += { data.pop() };
				bytes += bytes;
				for (int i = bytes.size() - 1; i >= 0; i--)
					data.push(bytes[i]);
				break;
			}
			case 9: {
				pushInt(instructions, PC, data);
				int offset = grabInt(data);
				if (grabInt(data) == grabInt(data))
					PC += offset;
				break;
			}
			case 10: {
				pushInt(instructions, PC, data);
				int offset = grabInt(data);
				if (grabInt(data) != grabInt(data))
					PC += offset;
				break;
			}
			case 11: {
				int val = grabInt(data) < grabInt(data);
				for (int i = 3; i >= 0; i--)
					data.push(val >> (8 * i));
				break;
			}
			case 12: {
				PC = grabInt(data) - 1;
				break;
			}
			case 13: {
				pushInt(instructions, PC, data);
				int val = grabInt(data) + grabInt(data);
				for (int i = 3; i >= 0; i--)
					data.push(val >> (8 * i));
				break;
			}
			case 14: {
				pushInt(instructions, PC, data);
				int val = grabInt(data) > grabInt(data);
				for (int i = 3; i >= 0; i--)
					data.push(val >> (8 * i));
				break;
			}
			default:
				break;
		}

		++PC;

		// showStackState(data);

	}

	return 0;

}

int main(int argc, char *argv[]) {

	if (argc != 2)
		return 1;

	Array<byte> instructions = loadFile(argv[1]);
	Stack<byte> data;
	
	return run(instructions, data);

}