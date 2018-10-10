#include <iostream>
#include <fstream>
#include "Headers/MemoryModels/Array.h"
#include "Headers/MemoryModels/Heap.h"
#include <ctime>

using namespace std;

int main(int argc, char **argv) {
	if (argc != 3) {
		cout << "Usage: sort <input file> <output file>" << endl;
		return -1; 
	}
	Array<int> data;
	string in;
	ifstream inFile;
	inFile.open(argv[1]);
	if (!inFile.is_open()) {
		cout << "Unable to open file: " << argv[1] << endl;
		return -1;
	}
	while (!inFile.eof()) {
		getline(inFile, in);
		while (in != "") {
			while (in != "") {
				data += stoi(in, nullptr, 10);
				if (in.find(",") == string::npos)
					in = "";
				else
					in = in.substr(in.find(",") + 1);
			}
			getline(inFile, in);
		}
	}
	inFile.close();
	ofstream outFile;
	outFile.open(argv[2]);
	if (!outFile.is_open()) {
		cout << "Unable to open file: " << argv[2] << endl;
		return -1;
	}
	long start = clock();
	Array<int> sorted = Heap<int>::sort(data).reverse();
	cout << "Heap Sort of " << data.size() << " items took " << double(clock() - start) / CLOCKS_PER_SEC * 1000 << " ms." << endl;
	for (int y = 0; y < sorted.size() / 15; y++) {
		for (int x = 0; x < 15; x++) {
			if (x < 14)
			  outFile << sorted[y * 15 + x] << ", ";
			else
				outFile << sorted[y * 15 + x];
		}
		if (y < sorted.size() / 15 - 1) 
			outFile << endl;
	}
	outFile.close();
	return 0;
}