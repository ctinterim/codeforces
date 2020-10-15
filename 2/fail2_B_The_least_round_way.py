from collections import namedtuple

Result = namedtuple('Result','cum2 cum5 last')

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

	# The first is trivial
	rmatrix[0][0] = Result(mat2[0][0], mat5[0][0], (0,0))

	# first row is trivial
	for c in range(1,n):
		cur2, cur5 = mat2[0][c], mat5[0][c]
		prev = rmatrix[0][c-1]
		rmatrix[0][c] = Result(prev.cum2+cur2, prev.cum5+cur5, (0,c-1))

	# first column is trivial
	for r in range(1,n):
		cur2, cur5 = mat2[r][0], mat5[r][0]
		prev = rmatrix[r-1][0]
		rmatrix[r][0] = Result(prev.cum2+cur2, prev.cum5+cur5, (r-1,0))

	# non-trivial cases
	for r in range(1,n):
		for c in range(1,n):
			cur2, cur5 = mat2[r][c], mat5[r][c]

			up = rmatrix[r-1][c]
			fu2, fu5 = cur2+up.cum2, cur5+up.cum5
			fu0 = min(fu2, fu5)

			left = rmatrix[r][c-1]
			fl2, fl5 = cur2+left.cum2, cur5+left.cum5
			fl0 = min(fl2, fl5)

			if fu0 < fl0:    # Get here from up
				rmatrix[r][c] = Result(fu2, fu5, (r-1,c))
			elif fl0 > fu0:  # Get here from left
				rmatrix[r][c] = Result(fl2, fl5, (r, c-1))
			else:


	# track from end
	r = n-1
	c = n-1
	path = []
	while (r > 0) or (c > 0):
		last = rmatrix[r][c].last
		if last == (r-1,c):
			path.append('D')
		else:
			path.append('R')
		r,c = last

	rd = rmatrix[n-1][n-1]
	print(min(rd.cum2, rd.cum5))
	print(''.join(path[::-1]))



			



