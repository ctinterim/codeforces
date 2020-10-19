def XORwice(a,b):
	x = 0
	for i in range(33):
		curbit = 1<<i
		if (a&curbit) and (b&curbit):
			x |= curbit
	return (a^x) + (b^x)


if __name__ == '__main__':
	t = int(input())
	for i in range(t):
		a,b = tuple(map(int, input().split()))
		res = XORwice(a,b)
		print(res)