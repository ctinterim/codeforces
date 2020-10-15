if __name__ == '__main__':
	for i in range(int(input())):
		iline = input()
		if len(iline) > 10:
			print(iline[0] + str(len(iline[1:-1])) + iline[-1])
		else:
			print(iline)