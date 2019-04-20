// computer.cpp
#include <iostream>
#include <fstream>
#include <string>
#include "computer.hpp"
using namespace std;

// Byte Order - Big Endian
void Computer::load(const char *program) {
	int i = 0;
	int j;
	string str;
	ifstream file;
	file.open(program);
	if (file) {
		// File loaded successfully
		// Fill memory with contents of program
		while (file >> str) {
			// Skip over comments
			if (str.find("--") != string::npos) {
				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			j = stol(str, nullptr, 16);
			for (int k = 0; k < 4; k++)
				memory[i + k] = (char) ((j >> (8 * (3 - k))) & 0xFF);
			i += 4;
		}
		// Fill the rest with noop
		while (i < MEMORY_BYTE_DEPTH)
			memory[i++] = (char) 0x00;
		// Initialize resgisters
		for (int k = 0; k < 32; k++)
			registerFile[k] = 0x00000000;
		// Initialize Stack Pointer
		registerFile[29] = MEMORY_BYTE_DEPTH - 4;
		// Initiliaze Return Address to know when to exit
		registerFile[31] = 0xFFFFFFFF;
	} else {
		cerr << "Unable to load program [" << program << "]" << endl;;
  	exit(1);   // Call system to stop
	}
	// Close the file
	file.close();
}

char Computer::getByte(int address) {
	return memory[address];
}

void Computer::storeByte(int address, char byte) {
	memory[address] = byte;
}

int Computer::getWord(int address) {
	if (address % 4) {
		cerr << "Word accessing must be word addressed (a % 4 = 0)." << endl;
  	exit(1);   // Call system to stop
	} else {
		int word = 0x00000000;
		for (int i = 0; i < 4; i++)
			word = word | ((((int) memory[address + i]) & 0xFF) << (8 * (3 - i)));
		return word;
	}
}

void Computer::storeWord(int address, int word) {
	if (address % 4) {
		cerr << "Word accessing must be word addressed (a % 4 = 0)." << endl;
		cout << word << endl;
  	exit(1);   // Call system to stop
	} else {
		for (int i = 0; i < 4; i++)
			memory[address + i] = (char) ((word >> (8 * (3 - i)) & 0xFF));
	}
}

int Computer::readRegister(int i) {
	return registerFile[i];
}

const int NEXT_PC = 0, BRANCH_PC = 1, JR_PC = 2, J_PC = 3;

void Computer::run() {
	while(true) {
		int instruction = getWord(programCounter);
		if (instruction == 0x00000000) {
			// noop
			programCounter += 4;
			continue;
		}
		int OPCode = (instruction >> 26) & 0b111111;
		int rs = (instruction >> 21) & 0b11111;
		int rt = (instruction >> 16) & 0b11111;
		int rd = (instruction >> 11) & 0b11111;
		int immediateValue = instruction & 0x0000FFFF;
		pc_mux = NEXT_PC;
		if (immediateValue >> 15)
			immediateValue = 0xFFFF0000 | immediateValue;
		if (OPCode == 0b111111) {
			// Termination Code
			break;
		} else if (OPCode == 0b000000) {
			// R-R Functions
			int function = instruction & 0b111111;
			if (function == 0b100000 || function == 0b100001) {
				// add and addu
				registerFile[rd] = registerFile[rs] + registerFile[rt];
			} else if (function == 0b100100) {
				// and
				registerFile[rd] = registerFile[rs] & registerFile[rt];
			} else if (function == 0b011010 || function == 0b011011) {
				// div and divu
				LO = registerFile[rs] / registerFile[rt];
				HI = registerFile[rs] % registerFile[rt];
			} else if (function == 0b001000) {
				// jr
				pc_mux = JR_PC;
			} else if (function == 0b010000) {
				// mfhi
				registerFile[rd] = HI;
			} else if (function == 0b010010) {
				// mflo
				registerFile[rd] = LO;
			} else if (function == 0b011000 || function == 0b011001) {
				// mult and multu
				LO = registerFile[rs] * registerFile[rt];
			} else if (function == 0b100101) {
				// or
				registerFile[rd] = registerFile[rs] | registerFile[rt];
			} else if (function == 0b000000) {
				// sll
				registerFile[rd] = registerFile[rt] << ((immediateValue >> 6) & 0x11111);
			} else if (function == 0b000100) {
				// sllv
				registerFile[rd] = registerFile[rt] << registerFile[rs];
			} else if (function == 0b101010) {
				// slt
				registerFile[rd] = registerFile[rs] < registerFile[rt] ? 1 : 0;
			} else if (function == 0b101011) {
				// sltu
				registerFile[rd] = ((unsigned) registerFile[rs] < (unsigned) registerFile[rt]) ? 1 : 0;
			} else if (function == 0b000011) {
				// sra
				registerFile[rd] = registerFile[rt] >> ((immediateValue >> 6) & 0x11111);
			} else if (function == 0b000010) {
				// srl
				registerFile[rd] = ((unsigned) registerFile[rt]) >> ((immediateValue >> 6) & 0x11111);
			} else if (function == 0b000110) {
				// srlv
				registerFile[rd] = ((unsigned) registerFile[rt]) >> registerFile[rs];
			} else if (function == 0b100010 || function == 0b100011) {
				// sub and subu
				registerFile[rd] = registerFile[rs] - registerFile[rt];
			} else if (function == 0b001100) {
				// syscall
				// software interrupt
			} else if (function == 0b100110) {
				// xor
				registerFile[rd] = registerFile[rs] ^ registerFile[rt];
			}
		} else {
			if (OPCode == 0b001000 || OPCode == 0b001001) {
				// addi and addiu
				registerFile[rt] = registerFile[rs] + immediateValue;
			} else if (OPCode == 0b001100) {
				// andi
				registerFile[rt] = registerFile[rs] & immediateValue;
			} else if (OPCode == 0b000100) {
				// beq
				if(registerFile[rs] == registerFile[rt])
					pc_mux = BRANCH_PC;
			} else if (OPCode == 0b000001) {
				// bgez and bgezal
				if(registerFile[rs] >= 0) {
					if (rt == 0b10001) {
						// bgezal
						registerFile[31] = programCounter + 4;
						pc_mux = BRANCH_PC;
					} else if (rt == 0b00001) {
						//bgez
						pc_mux = BRANCH_PC;
					}
				}
			} else if (OPCode == 0b000111) {
				// bgtz
				if (registerFile[rs] > 0) 
					pc_mux = BRANCH_PC;
			} else if (OPCode == 0b000110) {
				// blez
				if (registerFile[rs] <= 0)
					pc_mux = BRANCH_PC;
			} else if (OPCode == 0b000001) {
				// bltz and bltzal
				if (registerFile[rs] < 0){
					if (rt == 0b00000) {
						// bltz
						pc_mux = BRANCH_PC;
					} else if (rt == 0b10000) {
						// bltzal
						registerFile[31] = programCounter + 4;
						pc_mux = BRANCH_PC;
					}
				}
			} else if (OPCode == 0b000101) {
				// bne
				if (registerFile[rs] != registerFile[rt])
					pc_mux = BRANCH_PC;
			} else if (OPCode == 0b000010 || OPCode == 0b000011) {
				// j and jal
				if (OPCode == 0b000011) {
					// jal
					registerFile[31] = programCounter + 4;
				}
				pc_mux = J_PC;
			} else if (OPCode == 0b100000) {
				// lb
				registerFile[rt] = memory[registerFile[rs] + immediateValue];
			} else if (OPCode == 0b001111) {
				// lui
				registerFile[rt] = immediateValue << 16;
			} else if (OPCode == 0b100011) {
				// lw
				registerFile[rt] = getWord(registerFile[rs] + immediateValue);
			} else if (OPCode == 0b001101) {
				// ori
				registerFile[rt] = registerFile[rs] | immediateValue;
			} else if (OPCode == 0b101000) {
				// sb
				storeByte(registerFile[rs] + immediateValue, (char) (registerFile[rt] & 0xFF));
			} else if (OPCode == 0b001010) {
				// slti
				registerFile[rt] = registerFile[rs] < immediateValue ? 1 : 0;
			} else if (OPCode == 0b001011) {
				// sltiu
				registerFile[rt] = ((unsigned) registerFile[rs] < (unsigned) immediateValue) ? 1 : 0;
			} else if (OPCode == 0b101011) {
				// sw
				storeWord(registerFile[rs] + immediateValue, registerFile[rt]);
			} else if (OPCode == 0b001110) {
				// xori
				registerFile[rt] = registerFile[rs] ^ immediateValue;
			}
		}
		// Determines next instruction address based on current instruction.
		switch(pc_mux) {
			case NEXT_PC:
				programCounter += 4;
				break;
			case BRANCH_PC:
				programCounter += immediateValue << 2;
				break;
			case JR_PC:
				programCounter = registerFile[rs];
				if (programCounter == 0xFFFFFFFF)
					return;
				break;
			case J_PC:
				programCounter = (programCounter & 0xF0000000) | (immediateValue << 2);
				break;
			default:
				programCounter += 4;
				break;
		}
	}
}