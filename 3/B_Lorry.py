if __name__ == '__main__':
	n,v = tuple(map(int, input().split()))
	boats = []
	for i in range(n):
		t,c = tuple(map(int, input().split()))
		d = c/t
		if t == 1:
			d += 0.0000001
		boats.append((d,t,c,i+1))

	boats.sort(key=lambda tpl:tpl[0], reverse=True)

	sumt = 0
	sumc = 0
	boatorder = []
	last1 = None
	last1_idx = None

	for i in range(n):
		d,t,c,n = boats[i]

		if sumt + t <= v:
			boatorder.append(n)
			sumc += c
			sumt += t
			if t == 1:
				last1 = d,t,c,n
				last1_idx = len(boatorder)-1
		else:
			if last1 != None:
				l1d, l1t, l1c, l1n = last1
				if (sumc - l1c + c) > sumc:
					del boatorder[last1_idx]
					boatorder.append(n)
					sumc = sumc - l1c + c
					sumt = sumt - l1t + t

		if sumt == v:
			break

	print(sumc)
	print(' '.join(map(str,boatorder)))