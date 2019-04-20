#include <iostream>
#include "compiler.hpp"
using namespace std;

int main(int argc, char *argv[]) {
	if (argc < 3) {
		cerr << "Needs both a source and destination file." << endl;
		return 1;
	}
	compile(argv[1], argv[2]);
	return 0;
} 