if __name__ == '__main__':
	n,k,t = tuple(map(int, input().split()))
	p = int((n*k) * (0.01*t))

	res = []
	while p > 0:
		if p >= k:
			res.append(str(k))
			p -= k
		else:
			res.append(str(p))
			p = 0

	res = res + ['0']*(n-len(res))
	print(' '.join(res))