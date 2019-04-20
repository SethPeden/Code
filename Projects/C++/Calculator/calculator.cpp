#include <iostream>
#include "expression.h"
using namespace std;

int main() {
	string input;
	while (getline(cin, input)) {
		cout << Expression(input) << endl;
	}
}

// int main() {
// 	string input;
// 	Complex a, b;
// 	char op;
// 	while (true) {
// 		cout << "Enter 1st Operand: ";
// 		while(getline(cin, input)) {
// 			if (Patterns::Value.matches(input)) {
// 				a = Complex(input);
// 				break;
// 			}
// 		}
// 		cout << "Enter Operator: ";
// 		while(getline(cin, input)) {
// 			if (Patterns::Op.matches(input)) {
// 				op = input.at(0);
// 				break;
// 			}
// 		}
// 		cout << "Enter 2nd Operand: ";
// 		while(getline(cin, input)) {
// 			if (Patterns::Value.matches(input)) {
// 				b = Complex(input);
// 				break;
// 			}
// 		}
// 		cout << endl;
// 		switch (op) {
// 			case '+':
// 				cout << (a + b) << endl;
// 				break;
// 			case '-':
// 				cout << (a - b) << endl;
// 				break;
// 			case 'x':
// 				cout << (a * b) << endl;
// 				break;
// 			case '/':
// 				cout << (a / b) << endl;
// 				break;
// 		}
// 		cout << endl;
// 	}
// 	return 0;
// }