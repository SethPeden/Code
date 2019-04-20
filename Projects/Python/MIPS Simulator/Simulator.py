import sys
import os
from Data import *
from Executor import *
import math

class Simulator:
	""" MIPS Simulator """
	def __init__(self, filename, wordsize):
		self.filename = filename
		self.wordsize = wordsize
		# Setting up Registers
		self.registers = []
		for i in range(34):
			self.registers.append(Register(i, self.wordsize))
		self.memory = Memory(10000, self.wordsize)
		# Setting $29 (SP) to the highest memory value
		self.registers[29].set(self.memory.size)
		# Setting $31 (RA) to be greater than the instructions we can store. To know when to stop.
		self.registers[31].set(self.memory.size + 1)
		# Temp values to build memory
		self.state = BuilderState.NONE
		self.hold = []

		# Parsing input file for execution
		self.loadfile(self.filename)

	def loadfile(self, filename):
		with open(self.filename, "r") as file:
			lines = file.readlines()
			for l in lines:
				c = False
				# Tokenizing each line
				for s in l.strip().split("\t"):
					for t in s.split(" "):
						for token in t.replace(")", "").split("("):
							if (not token == ""):
								# Non whitespace groups make it here
								if (not "#" in token):
									# Only code fragments make it here
									if ("." in token):
										# Directive
										if (self.state == BuilderState.STATIC):
											self.hold.append(token.replace(".", ""))
										else:
											pass
									elif(':' in token):
										# Label
										if (self.state == BuilderState.NONE):
											self.state = BuilderState.STATIC
											self.hold.append(token.replace(":", ""))
										else:
											pass
									elif("$" in token):
										# Register
										if (self.state == BuilderState.CODE):
											self.hold.append(int(token.replace("$", "").replace(",", "")))
									else:
										# Operation or Immediate Value
										if (token in MIPS_Opcodes):
											self.state = BuilderState.CODE
											if (self.hold == []):
												self.hold.append(None)
											self.hold.append(token)
										elif (self.state == BuilderState.CODE):
											if (token.isdigit()):
												self.hold.append(int(token))
											elif (token.startswith("-") and token[1:].isdigit()):
												self.hold.append(-int(token[1:]))
											elif ("x" in token):
												self.hold.append(self.hex_to_signed_int(token, 16))
										elif (self.state == BuilderState.STATIC):
											self.hold.append(token.replace(",", ""))
										else:
											pass
								else:
									c = True
									break
						if (c): break
					if (c): break

				# Add line to memory
				if (self.state == BuilderState.STATIC):
					if (not self.hold == []):
						self.memory.insert(self.hold, "STATIC")
					self.hold = []
					self.state = BuilderState.NONE
				elif(self.state == BuilderState.CODE):
					if (not self.hold == []):
						self.memory.insert(self.hold, "CODE")
					self.hold = []
					self.state = BuilderState.NONE

			file.close()

	def view(self):
		# Clears the terminal output
		os.system('cls' if os.name == 'nt' else 'clear')
		for j in range(len(self.registers) / 2):
			for i in range(2):
				r = j * 2 + i
				v = "--" if self.registers[r].get() == None else self.registers[r].get()
				print "${}: {}\t\t\t\t".format(r, v),
			print

	# hex string to signed integer
	def hex_to_signed_int(self, val, bits):
		val = val[2:]
		if (len(val) < 4):
			val = "0" * (8 - len(val)) + val
		if (len(val) < 8):
			if (int(str(val[0]), 16) > 7):
				val = "F" * (8 - len(val)) + val
			else:
				val = "0" * (8 - len(val)) + val
		n = list(int(i, 16) for i in val)
		if (n[0] < 8):
			return (int(val, 16) % (2 ** (bits - 1)))
		else:
			nc = list(15 - i for i in n)
			nc[len(nc) - 1] += 1
			for i in range(len(nc) - 1, 1, -1):
				if (nc[i] == 16):
					nc[i] = 0
					nc[i - 1] += 1
			new_val = "".join(list(hex(i) for i in nc)).replace("0x", "")
			return -(int(new_val, 16) % (2 ** (bits - 1)))

class BuilderState:
    NONE = 0
    STATIC = 1
    CODE = 2

if __name__ == "__main__":
	Sim = Simulator("/Users/Seth/Desktop/MIPS Simulator/example.asm", 32)
	ex = Executor(Sim.memory.initialize(), Sim.registers)
	while (ex.can_execute()):
		Sim.registers = ex.execute()
		Sim.view()
		raw_input("")