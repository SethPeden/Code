class Register:
	""" Registers for use in MIPS Architecture """
	def __init__(self, id, wordsize):
		self.id = id
		self.value = 0 if self.id == 0 else None
		self.wordsize = wordsize

	def set(self, value):
		if (self.id == 0):
			print "You shouldn't alter $0!"
		else:
			if (value < 0):
				self.value = -(-value % (2 ** (self.wordsize - 1)))
			else:
				self.value = value % (2 ** (self.wordsize - 1))
		return self.value

	def get(self):
		return self.value

class Memory:
	""" Memory for use in MIPS Architecture """
	def __init__(self, size, wordsize):
		self.size = size
		self.data = []
		for i in range(self.size):
			self.data.append(None)
		self.wordsize = wordsize
		self.static = {}
		self.lines = []

	def insert(self, data, type):
		if (type == "STATIC"):
			if (data[1] == "word"):
				self.static[data[0]] = list(int(s) for s in data[2:])
			elif (data[1] == "alloc"):
				a = []
				for i in range(int(data[2])):
					a.append(None)
				self.static[data[0]] = a
		if (type == "CODE"):
			self.lines.append(data)

	def initialize(self):
		for i in range(len(self.lines)):
			self.data[4 * i] = self.lines[i]
		for i in range(len(self.static)):
			self.data[4 * (i + len(self.lines))] = [self.static.keys()[i], [self.static[self.static.keys()[i]]]]

		return self.data