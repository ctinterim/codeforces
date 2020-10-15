from collections import namedtuple

Result = namedtuple('Result','cum2 cum5 way')

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

	rmatrix = [[None]*n for i in range(n)]

	# The last is trivial
	rmatrix[n-1][n-1] = Result(mat2[n-1][n-1], mat5[n-1][n-1], '')

	# last row is trivial
	for c in range(n-2,-1,-1):
		cur2, cur5 = mat2[n-1][c], mat5[n-1][c]
		prev = rmatrix[n-1][c+1]
		rmatrix[n-1][c] = Result(prev.cum2+cur2, prev.cum5+cur5, 'R')

	# last column is trivial
	for r in range(n-2, -1, -1):
		cur2, cur5 = mat2[r][n-1], mat5[r][n-1]
		prev = rmatrix[r+1][n-1]
		rmatrix[r][n-1] = Result(prev.cum2+cur2, prev.cum5+cur5, 'D')

	# calculate nontrivial case
	for r in range(n-2, -1, -1):
		for c in range(n-2, -1, -1):
			cur2, cur5 = mat2[r][c], mat5[r][c]
			right = rmatrix[r][c+1]
			down = rmatrix[r+1][c]

			r2,r5 = right.cum2+cur2,right.cum5+cur5
			d2,d5 = down.cum2+cur2, down.cum5+cur5
			r0 = min(r2,r5)
			d0 = min(d2,d5)

			if r0 < d0:
				rmatrix[r][c] = Result(r2, r5, 'R')
			elif d0 > r0:
				rmatrix[r][c] = Result(d2, d5, 'D')
			else:
				


	path = []
	r,c = 0,0
	while (r < n-1) or (c < n-1):
		if rmatrix[r][c].way == 'R':
			path.append('R')
			c += 1
		else:
			path.append('D')
			r += 1

	fa = rmatrix[0][0]
	print(min(fa.cum2, fa.cum5))
	print(''.join(path))