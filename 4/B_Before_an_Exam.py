if __name__ == '__main__':
	d, sumTime = tuple(map(int, input().split()))
	minT, maxT = [0]*d, [0]*d
	for i in range(d):
		minT[i], maxT[i] = tuple(map(int, input().split()))

	sumMinT, sumMaxT = sum(minT), sum(maxT)

	if sumMinT > sumTime:
		print('NO')
	elif sumMaxT < sumTime:
		print('NO')
	else:
		print('YES')
		result = []
		extraT = sumTime - sumMinT
		for i in range(d):
			if extraT > 0:
				curMaxExtra = maxT[i]-minT[i]
				curExtra = curMaxExtra if curMaxExtra < extraT else extraT
				result.append(str(minT[i] + curExtra))
				extraT -= curExtra
			else:
				result.append(str(minT[i]))
		print(' '.join(result))