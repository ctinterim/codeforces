if __name__ == '__main__':
	n = int(input())
	hill = list(map(int,input().split()))

	maxh = -1
	maxhi = -1
	sumh = 0

	for i in range(n):
		if hill[i] > maxh:
			maxh = hill[i]
			maxhi = i
		sumh += hill[i]

	# handle special case - everything is the same
	if sumh == maxh * n:
		print((n*(n-1))//2)
		exit()

	chain = [maxh] + hill[maxhi+1:] + hill[:maxhi] + [maxh]
	print(chain)

	L = [0]*len(chain)
	L_hi = [0]*len(chain)
	R = [0]*len(chain)
	R_visited = [False]*len(chain)

	# calculate left
	for i in range(1,len(chain)-1):
		if L[i] > 0:
			continue

		same = []
		higher = i
		for j in range(i+1, len(chain)):
			if chain[i] == chain[j]:
				same.append(j)
			elif chain[i] < chain[j]:
				higher = j
				break

		L_hi[i] = higher
		L[i] = 1 + len(same) + 1
		if (len(same) > 0 and i+1 == same[0]) or i+1 == higher:
			L[i] -= 1

		S_i = L[i] - 1
		for s in same:
			L[s] = S_i
			L_hi[s] = higher
			S_i -= 1

	# calculate right
	for i in range(len(chain)-2, 0, -1):
		if R_visited[i]:
			continue

		R_visited[i] = True
		same = []
		higher = i
		for j in range(i-1, -1, -1):
			if chain[i] == chain[j]:
				same.append(j)
			elif chain[i] < chain[j]:
				higher = j
				break

		R[i] = 1
		if (i != 1 and higher == i-1) or (L_hi[i] == len(chain)-1 and higher == 0):
			R[i] = 0

		for s in same:
			R_visited[s] = True
			if higher == s-1:
				R[s] = 0
			else:
				R[s] = R[i]

	print('L')
	for i in range(len(chain)):
		print(i,chain[i],L[i])
	print('R')
	for i in range(len(chain)):
		print(i,chain[i],R[i])

	print(sum(L)+sum(R))