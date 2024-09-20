import sys

inFile = sys.argv[1]
file = open(inFile, "r")
lines = file.readlines()
file.close()
file = open(inFile, "w")
for line in lines:
    if line.upper() != line:
        for k in range(len(line)):
            if line[k].isalpha():
                file.write(line[k:])
                break
file.write('\n')
file.close()
