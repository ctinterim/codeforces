import math
 
POW26 = [int(math.pow(26,i)) for i in range(7)]
 
def interpretRXCY(line):
	if line[0] != 'R':
		return False
 
	idxC = line.find('C')
	if idxC < 0:
		return False
 
	rp, cp = line[1:idxC], line[idxC+1:]
 
	if rp.isdigit() and cp.isdigit():
		return int(rp), int(cp)
	else:
		return False
 
def printRXCY(row,col):
	print('R{}C{}'.format(row,col))
 
def interpretExcel(line):
	for i in range(len(line)):
		if line[i].isdigit():
			rowbeg = i
			break
 
	colpart = line[:rowbeg]
	col = 0
	for i in range(len(colpart)):
		curpow = len(colpart) - i -1
		coeff = ord(colpart[i]) - ord('A') + 1
		col += POW26[curpow] * coeff
		
	row = int(line[rowbeg:])
	return row, col
 
def printExcel(row, col):
	colpart = ['A']
	colsum = 1
	for i in range(1, 7):
		if (colsum + POW26[i] >= col):
			break
		colpart.append('A')
		colsum += POW26[i]
 
	col -= colsum
	for i in range(len(colpart)):
		curpow = len(colpart) - i - 1
		div = col // POW26[curpow]
		if div > 0:
			rem = col % POW26[curpow]
			colpart[i] = chr(ord('A') + div)
			col = rem
 
	colpart = ''.join(colpart)
	print(colpart + str(row))
 
 
 
if __name__ == '__main__':
	n = int(input())
	for i in range(n):
		line = input()
		rxcy = interpretRXCY(line)
		if rxcy:
			row,col = rxcy
			printExcel(row, col)
		else:
			row,col = interpretExcel(line)
			printRXCY(row, col)