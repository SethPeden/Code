// compiler.cpp
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "compiler.hpp"
#include "computer.hpp"
using namespace std;

string instrs = "instructions.txt";
int instructionCount = 0;
int instructions[MEMORY_BYTE_DEPTH];

string getBitTemplate(string instr) {
	string t;
	stringstream ss;
	ss.str(instrs.substr(instrs.find(instr)));
	getline(ss, t);
	getline(ss, t);
	return t;
}

int encode(string str) {
	int val = 0;
	// 0bstdhi
	char type = 0b00000; 
	// int br1 = (str.find(" ") != string::npos) ? str.find(" ") : str.back();
	// int br2 = (str.find("\t") != string::npos) ? str.find("\t") : str.back();
	size_t br1 = str.find(" ");
	size_t br2 = str.find("\t");
	string instr = str.substr(0, min(br1, br2));
	string args;
	if (br1 == string::npos and br2 == string::npos)
		args = "";
	else
		args = str.substr(min(br1, br2));
	stringstream ss;
	ss.str(args);
	string templ = getBitTemplate(instr);
	if (templ.find("s") != string::npos)
		type = type | 0b10000;
	if (templ.find("t") != string::npos)
		type = type | 0b01000;
	if (templ.find("d") != string::npos)
		type = type | 0b00100;
	if (templ.find("h") != string::npos)
		type = type | 0b00010;
	if (templ.find("i") != string::npos)
		type = type | 0b00001;
	string s = "", t = "", d = "", h = "", i = "", a;
	switch (type) {
		case 0b11100:
			// std
			// Encode d
			ss >> d;
			d.replace(d.find("$"), 1, "").replace(d.find(","), 1, "");
			// Encode s
			ss >> s;
			s.replace(s.find("$"), 1, "").replace(s.find(","), 1, "");
			// Encode t
			ss >> t;
			t.replace(t.find("$"), 1, "");
			break;
		case 0b11001:
			// sti
			// Encode t
			ss >> t;
			t.replace(t.find("$"), 1, "").replace(t.find(","), 1, "");
			ss >> a;
			if (a.find("(") != string::npos) {
				// lb, sb, lw, sw
				// Encode imm
				i = a.substr(0, a.find("("));
				// Encode s
				s = a.substr(a.find("(") + 2, a.find(")"));
			} else {
				// Encode s
				s = a.replace(a.find("$"), 1, "").replace(a.find(","), 1, "");
				// Encode imm
				ss >> i;
			}
			break;
		case 0b10001:
			// si
			// Encode s
			ss >> s;
			s.replace(s.find("$"), 1, "").replace(s.find(","), 1, "");
			// Encode i
			ss >> i;
			break;
		case 0b11000:
			// st
			// Encode s
			ss >> s;
			s.replace(s.find("$"), 1, "").replace(s.find(","), 1, "");
			// Encode t
			ss >> t;
			t.replace(t.find("$"), 1, "");
			break;
		case 0b00001:
			// i
			// Encode i
			ss >> i;
			break;
		case 0b10000:
			// s
			// Encode s
			ss >> s;
			s.replace(s.find("$"), 1, "");
			break;
		case 0b01001:
			// ti
			// Encode t
			ss >> t;
			t.replace(t.find("$"), 1, "").replace(t.find(","), 1, "");
			// Encode i
			ss >> i;
			break;
		case 0b00100:
			// d
			// Encode d
			ss >> d;
			d.replace(d.find("$"), 1, "");
			break;
		case 0b00000:
			// noop or syscall
			break;
		case 0b01110:
			// tdh
			// Encode d
			ss >> d;
			d.replace(d.find("$"), 1, "").replace(d.find(","), 1, "");
			// Encode t
			ss >> t;
			t.replace(t.find("$"), 1, "").replace(t.find(","), 1, "");
			// Encode h
			ss >> h;
			break;
		default:
			break;
	}
	if (s != "")
		templ.replace(templ.find("s"), 1, bitset<5>(stoi(s, nullptr, 10)).to_string());
	if (t != "")
		templ.replace(templ.find("t"), 1, bitset<5>(stoi(t, nullptr, 10)).to_string());
	if (d != "")
		templ.replace(templ.find("d"), 1, bitset<5>(stoi(d, nullptr, 10)).to_string());
	if (h != "") {
		if (h.find("b") != string::npos)
			h = bitset<5>(stoi(h.substr(h.find("b") + 1), nullptr, 2)).to_string();
		else if (h.find("x") != string::npos)
			h = bitset<5>(stoi(h.substr(h.find("b") + 1), nullptr, 16)).to_string();
		else
			h = bitset<5>(stoi(h, nullptr, 10)).to_string();
		templ.replace(templ.find("h"), 1, h);
	} 
	if (i != "") {
		if (instr == "j" || instr == "jal") {
			if (i.find("b") != string::npos)
				i = bitset<26>(stoi(i.substr(i.find("b") + 1), nullptr, 2)).to_string();
			else if (i.find("x") != string::npos)
				i = bitset<26>(stoi(i.substr(i.find("b") + 1), nullptr, 16)).to_string();
			else
				i = bitset<26>(stoi(i, nullptr, 10)).to_string();
		} else {
			if (i.find("b") != string::npos)
				i = bitset<16>(stoi(i.substr(i.find("b") + 1), nullptr, 2)).to_string();
			else if (i.find("x") != string::npos)
				i = bitset<16>(stoi(i.substr(i.find("b") + 1), nullptr, 16)).to_string();
			else
				i = bitset<16>(stoi(i, nullptr, 10)).to_string();
		}
		templ.replace(templ.find("i"), 1, i);
	}
	val = (int) bitset<32>(templ).to_ulong();
	return val;
}

void compile(const char *program, const char *binary) {
	string str, line, temp, code = "";
	ifstream file;
	file.open(instrs);
	if (file) {
		// File loaded successfully
		instrs = "";
		while (file >> str)
			instrs += str + "\n";
	}
	file.close();
	file.open(program);
	if (file) {
		// File loaded successfully
		while (getline(file, str)) {
			line = str;
			// Skip over comments
			if (str.find("#") != string::npos)
				str = str.substr(0, str.find("#"));
			stringstream ss;
			ss << setfill('0') << setw(8) << hex << encode(str);
			temp = ss.str();
			transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
			code += temp + "\t\t-- " + line + "\n";
		}
		// We have encoded the file
	}
	file.close();
	ofstream out;
	out.open(binary);
	if (out.is_open()) {
		// Write data to file
		out << code;
	}
	out.close();
}