// main.cpp
#include <iostream>
#include "computer.hpp"
#include "compiler.hpp"
using namespace std;

int main(int argc, char *argv[]) {

	if (argc < 2) {
		cerr << "Need an input file to run." << endl;
		return 1;
	}

	Computer comp;
	comp.load(argv[1]);
	comp.run();

	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 4; i++) {
			cout << dec << "$" << (j * 4 + i) << ":\t" << hex << comp.readRegister(j * 4 + i) << "\t";
		}
		cout << endl;
	}
	
}