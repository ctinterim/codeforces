import random

def results(mat, r, c, a, b):
	minval = 0xFFFFFFFF
	sumval = 0
	cost = 0
	for rr in range(r,r+a):
		for cc in range(c,c+b):
			if mat[rr][cc] < minval:
				minval = mat[rr][cc]
			sumval += mat[rr][cc]

	return minval, sumval, sumval - (minval*a*b)

if __name__ == '__main__':
	n = 10
	m = 10
	for i in range(1):
		a = random.randint(1,n)
		b = random.randint(1,m)
		mat = [[random.randint(0,9) for c in range(m)] for r in range(n)]

		with open('inputs/input_{}'.format(i),'w') as ofile:
			ofile.write('{} {} {} {}\n'.format(n,m,a,b))
			for r in range(n):
				ofile.write(' '.join(map(str,mat[r])))
				ofile.write('\n')

		pmfile = open('inputs/partialmin_{}'.format(i),'w')
		psfile = open('inputs/partialsum_{}'.format(i),'w')
		ctfile = open('inputs/cost_{}'.format(i),'w')

		for row in range(0, n-a+1):
			print(row,'/',n-a+1)
			pml = []
			psl = []
			ctl = []
			for col in range(0, m-b+1):
				minval, sumval, cost = results(mat,row,col,a,b)
				pml.append(minval)
				psl.append(sumval)
				ctl.append(cost)

			pmfile.write(' '.join(map(str,pml)) + '\n')
			psfile.write(' '.join(map(str,psl)) + '\n')
			ctfile.write(' '.join(map(str,ctl)) + '\n')

		pmfile.close()
		psfile.close()
		ctfile.close()			