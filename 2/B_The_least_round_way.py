from collections import namedtuple

Path = namedtuple('Path','sum2 sum5 next')

def numDiv(num, div):
	res = 0
	while num > 1:
		if num % div > 0:
			break
		res += 1
		num = num // div
	return res

if __name__ == '__main__':
	n = int(input())
	imatrix = []
	for i in range(n):
		imatrix.append(list(map(int,input().split())))

	mat2, mat5 = [[0]*n for i in range(n)], [[0]*n for i in range(n)]

	for i in range(n):
		for j in range(n):
			mat2[i][j] = numDiv(imatrix[i][j],2)
			mat5[i][j] = numDiv(imatrix[i][j],5)

	path2 = [[None]*n for i in range(n)]
	path5 = [[None]*n for i in range(n)]

	rd = Path(mat2[n-1][n-1], mat5[n-1][n-1], '')
	path2[n-1][n-1] = rd
	path5[n-1][n-1] = rd

	# last row is trivial
	for c in range(n-2, -1, -1):
		goright = Path(path2[n-1][c+1].sum2 + mat2[n-1][c], path2[n-1][c+1].sum5 + mat5[n-1][c], 'R')
		path2[n-1][c] = goright
		path5[n-1][c] = goright

	# last column is trivial
	for r in range(n-2, -1, -1):
		godown  = Path(path2[r+1][n-1].sum2 + mat2[r][n-1], path2[r+1][n-1].sum5 + mat5[r][n-1], 'D')
		path2[r][n-1] = godown
		path5[r][n-1] = godown

	# Non-trivial cases
	for r in range(n-2, -1, -1):
		for c in range(n-2, -1, -1):
			cur2, cur5 = mat2[r][c], mat5[r][c]
			# For 2
			right2 = path2[r][c+1]
			down2  = path2[r+1][c]
			if right2.sum2 < down2.sum2:
				path2[r][c] = Path(right2.sum2 + cur2, right2.sum5 + cur5, 'R')
			else:
				path2[r][c] = Path( down2.sum2 + cur2,  down2.sum5 + cur5, 'D')

			# For 5
			right5 = path5[r][c+1]
			down5  = path5[r+1][c]
			if right5.sum5 < down5.sum5:
				path5[r][c] = Path(right5.sum2 + cur2, right5.sum5 + cur5, 'R')
			else:
				path5[r][c] = Path( down5.sum2 + cur2,  down5.sum5 + cur5, 'D')

	res2, res5 = min(path2[0][0].sum2, path2[0][0].sum5), min(path5[0][0].sum2, path5[0][0].sum5)

	path = path2 if (res2 < res5) else path5

	r,c = 0,0
	pathlist = []
	while (r < n) or (r < c):
		mv = path[r][c].next
		pathlist.append(mv)
		if mv == 'R':
			c += 1
		else:
			r += 1

	print(min(res2,res5))
	print(''.join(pathlist))