from sys import stdin
 
if __name__ == '__main__':
	lines = []
 
	for line in stdin:
		lines.append(line.strip())
 
	maxwidth = max([len(l) for l in lines])
 
	alignleft = True
	print('*'*(maxwidth+2))
	for l in lines:
		if ((maxwidth - len(l)) & 1) == 0:
			print('*'+l.center(maxwidth,' ')+'*')
		else:
			if alignleft:
				ls = (maxwidth - len(l)) // 2
				rs = ls + 1
				alignleft = False
			else:
				rs = (maxwidth - len(l)) // 2
				ls = rs + 1
				alignleft = True
			print('*' + ' '*ls + l + ' '*rs + '*')
	print('*'*(maxwidth+2))