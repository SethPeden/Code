import sys
import os

file_name = os.path.dirname(os.path.abspath(__file__)) + "/file.txt"

with open(file_name, "w") as file:
	file.write("-")
	file.close()

for i in range(0, int(sys.argv[1])):
	with open(file_name, "r+") as file:
		file.write(file.read())
		file.close()