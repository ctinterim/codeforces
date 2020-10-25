import random

def minElement(mat, r, c, a, b):
	minval = 0xFFFFFFFF
	for rr in range(r,r+a):
		for cc in range(c,c+b):
			if mat[rr][cc] < minval:
				minval = mat[rr][cc]
	return minval

if __name__ == '__main__':
	n = 100
	m = 100
	for i in range(1):
		a = random.randint(1,n)
		b = random.randint(1,m)
		mat = [[random.randint(0,1000000000) for c in range(m)] for r in range(n)]

		with open('inputs/input_{}'.format(i),'w') as ofile:
			ofile.write('{} {} {} {}\n'.format(n,m,a,b))
			for r in range(n):
				ofile.write(' '.join(map(str,mat[r])))
				ofile.write('\n')

		with open('inputs/solution_{}'.format(i), 'w') as ofile:
			for row in range(0, n-a+1):
				print(row,'/',n-a+1)
				rsol = []
				for col in range(0, m-b+1):
					rsol.append(minElement(mat,row,col,a,b))
				ofile.write(' '.join(map(str,rsol)))
				ofile.write('\n')