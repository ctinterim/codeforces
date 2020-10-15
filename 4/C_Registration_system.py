if __name__ == '__main__':
	N = int(input())
	namedict = {}
	for i in range(N):
		name = input().strip()
		if name not in namedict:
			namedict[name] = 0
			print('OK')
		else:
			namedict[name] += 1
			print('{}{}'.format(name, namedict[name]))