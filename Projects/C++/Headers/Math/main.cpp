// main.cpp
// Seth Peden
// 2-19-18 11:05:00 PM

#include <iostream>
#include <string>
#include "fraction.hpp"
using namespace std;

string in;
string operands[2];
char operation;

bool readLine(istream &is) {
	getline(is, in);
	return in != "";
}

void parse(string s) {
	int i = 0;
	while (s[i] != '+' and s[i] != '-' and s[i] != '*' and s[i] != 'd') {
		i++;
	}
	if (i < s.length())
		operation = s[i];
	else 
		operation = '\0';
	operands[0] = s.substr(0, i);
	if (i + 1 < s.length()) 
		operands[1] = s.substr(i + 1);
	else 
		operands[1] = "";
	for (int j = 0; j < 2; j++) {
		for (int k = 0; k < operands[j].length(); k++) {
			if (operands[j][k] == ' ') {
				operands[j].replace(k, 1, "");
			}
		}
	}
}

int main() {
	Fraction answer = 0L, a, b;
	while (readLine(cin)) {
		parse(in);
		if (in == "") {
			break;
		}
		if (operands[0] != "") {
			if (operation and operands[1] == "") {
				cout << "invalid expression" << endl;
				continue;
			} else if (operands[1] == "") {
				answer = Fraction(operands[0]);
				cout << "\t= " << answer << endl;
				continue;
			}
			a = Fraction(operands[0]);
		} else {
			a = answer;
		}
		if (operands[1] != "") {
			b = Fraction(operands[1]);
		} else {
			if (operation) {
				cout << "invalid expression" << endl;
				continue;
			} else {
				return 0;
			}
		}
		switch (operation) {
					case '+':
						answer = a + b;
						break;
					case '-':
						answer = a - b;
						break;
					case '*':
						answer = a * b;
						break;
					case 'd':
						answer = a / b;
						break;
					default:
						break;
		}
		cout << "\t= " << answer << endl;
	}
	return 0;
}