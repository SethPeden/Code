MIPS_Opcodes = ['add', 'sub', 'addi', 'addu', 'subu', 'addiu', \
                'mult', 'multu', 'div', 'divu', 'mfhi', 'mflo', 'and', \
                'or', 'andi', 'ori', 'nor', 'xor', 'xori', 'sll', 'sllv', \
                'srl', 'srlv', 'sra', 'srav', 'lw', 'sw', 'lb', 'lbu', 'sb', \
                'lui', 'beq', 'bne', 'slt', 'slti', 'sltu', 'sltui', 'j', \
                'jr', 'jal', 'swi', 'cid', 'nc', 'llw', 'stcw']

class Executor:
	def __init__(self, data, registers):
		self.data = data
		self.program_counter = 0
		self.stack_pointer = len(self.data) - 4
		self.registers = registers

	def can_execute(self):
		line = self.data[self.program_counter]
		return not line[1] == "jr" or (self.registers[line[2]] >= 0 and self.registers[line[2]] < len(self.data))

	def execute(self):
		line = self.data[self.program_counter]
		if (line[1] == "add"):
			self.registers[line[2]].set(self.registers[line[3]].get() + self.registers[line[4]].get())
		elif (line[1] == "sub"):
			self.registers[line[2]].set(self.registers[line[3]].get() - self.registers[line[4]].get())
		elif (line[1] == "addi"):
			self.registers[line[2]].set(self.registers[line[3]].get() + line[4])
		elif (line[1] == "addu"):
			r1 = self.registers[line[3]].get()
			if (r1 < 0):
				h = hex(r1).replace("0x", "").replace("-", "")
				r1 = int("F" * (8 - len(h)) + h, 16)
			r2 = self.registers[line[4]].get()
			if (r2 < 0):
				h = hex(r2).replace("0x", "").replace("-", "")
				r2 = int("F" * (8 - len(h)) + h, 16)	
			self.registers[line[2]].set(r1 + r2)
		elif (line[1] == "subu"):
			r1 = self.registers[line[3]].get()
			if (r1 < 0):
				h = hex(r1).replace("0x", "").replace("-", "")
				r1 = int("F" * (8 - len(h)) + h, 16)
			r2 = self.registers[line[4]].get()
			if (r2 < 0):
				h = hex(r2).replace("0x", "").replace("-", "")
				r2 = int("F" * (8 - len(h)) + h, 16)	
			self.registers[line[2]].set(r1 - r2)
		elif (line[1] == "addiu"):
			r1 = self.registers[line[3]].get()
			if (r1 < 0):
				h = hex(r1).replace("0x", "").replace("-", "")
				r1 = int("F" * (8 - len(h)) + h, 16)
			r2 = line[4]
			if (r2 < 0):
				if ("0x" in str(r2)):
					h = hex(str(r2)).replace("0x", "").replace("-", "")
					r2 = int("F" * (8 - len(h)) + h, 16)
				else:
					r2 = -r2
			self.registers[line[2]].set(r1 + r2)
		elif (line[1] == "mult"):
			prod = self.registers[line[2]].get() * self.registers[line[3]].get()
			if (prod >= 0):
				lo = prod % (2 ** 31)
				hi = prod >> 32
			else:
				lo = -(-prod % (2 ** 31))
				hi = -(-prod >> 32)
			self.registers[32].set(hi)
			self.registers[33].set(lo)
		elif (line[1] == "multu"):
			r1 = self.registers[line[2]].get()
			if (r1 < 0):
				h = hex(r1).replace("0x", "").replace("-", "")
				r1 = int("F" * (8 - len(h)) + h, 16)
			r2 = self.registers[line[3]].get()
			if (r2 < 0):
				h = hex(r2).replace("0x", "").replace("-", "")
				r2 = int("F" * (8 - len(h)) + h, 16)	
			prod = r1 * r2
			lo = prod % (2 ** 31)
			hi = prod >> 32
			self.registers[32].set(hi)
			self.registers[33].set(lo)

		else:
			print "{} is unsupported".format(line[1])
		
		self.program_counter += 4
		return self.registers