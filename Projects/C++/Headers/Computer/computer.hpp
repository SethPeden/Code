// computer.hpp
#ifndef COMPUTER_HPP
#define COMPUTER_HPP
#define MEMORY_BYTE_DEPTH 0x00100000

// Byte Order - Big Endian
class Computer {

	private:
	int programCounter = 0x00000000;
	char memory[MEMORY_BYTE_DEPTH];
	int registerFile[32];
	int HI, LO;
	int pc_mux = 0;

	public:
	void load(const char *program);
	char getByte(int address);
	void storeByte(int address, char byte);
	int getWord(int address);
	void storeWord(int address, int word);
	int readRegister(int i);
	void run();

};

#endif