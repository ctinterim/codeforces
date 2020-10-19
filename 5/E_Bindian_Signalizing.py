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
	# print(chain)

	L = [0]*len(chain)
	L_hi = [0]*len(chain)
	L_numsame = [0]*len(chain)

	R = [0]*len(chain)
	R_hi = [len(chain)-1]*len(chain)

	# calculate left to right
	for i in range(1,len(chain)-1):
		if i == len(chain)-2:
			L[i] = 1
			L_hi[i] = len(chain)-1
			L_numsame[i] = 0
			continue

		if L_hi[i] == 0:
			same = []
			higher = len(chain)-1
			for j in range(i+1, len(chain)):
				if j != len(chain)-1 and chain[i] == chain[j]:
					same.append(j)
				elif chain[i] < chain[j]:
					higher = j
					break
			L_hi[i] = higher
			L_numsame[i] = len(same)
			L_numsame_s = L_numsame[i] - 1
			for s in same:
				L_hi[s] = higher
				L_numsame[s] = L_numsame_s
				L_numsame_s -= 1

		L[i] = 1 + L_numsame[i] + 1 # connection with neighbor, same, and higher

		# if neighbor and i are same, it is duplicate so erase
		if (L_numsame[i] > 0 and chain[i] == chain[i+1]):
			L[i] -= 1
		# if neighbor is higher, and the value is actually bigger, then it is duplicate so erase
		if i+1 == L_hi[i] and chain[i] < chain[L_hi[i]]:
			L[i] -= 1

	# calculate right to left
	for i in range(len(chain)-2, 0, -1):
		if R_hi[i] == len(chain)-1:
			same = []
			higher = 0
			for j in range(i-1, -1, -1):
				if j != 0 and chain[i] == chain[j]:
					same.append(j)
				elif chain[i] < chain[j]:
					higher = j
					break

			R_hi[i] = higher
			for s in same:
				R_hi[s] = higher
	
		R[i] = 1 # connection with strictly higher

		if chain[i] == maxh:
			R[i] = 0
		elif R_hi[i] == 0 and L_hi[i] == len(chain)-1: # if l->r higher was right end and r->l higher is left end, do not add
			R[i] = 0
		elif i > 1 and R_hi[i] == i-1: # if strictly higher is neighbor, do not add
			R[i] = 0
		

	# print('L')
	# for i in range(len(chain)):
	# 	print(i,chain[i],L[i])
	# print('R')
	# for i in range(len(chain)):
	# 	print(i,chain[i],R[i])

	print(sum(L)+sum(R))