if __name__ == '__main__':
	n,m,color = input().split()
	n,m = int(n), int(m)
	dmap = []
	for i in range(n):
		dmap.append(input())

	lur, luc = -1, -1
	for r in range(n):
		for c in range(m):
			if dmap[r][c] == color:
				lur = r
				luc = c
				break
		if lur != -1 and luc != -1:
			break

	rdr, rdc = -1, -1
	for r in range(n-1,-1,-1):
		for c in range(m-1,-1,-1):
			if dmap[r][c] == color:
				rdr = r
				rdc = c
				break
		if rdr != -1 and rdr != -1:
			break

	rset = set([])
	if lur > 0:
		for c in range(luc,rdc+1):
			rset.add(dmap[lur-1][c])
	if luc > 0:
		for r in range(lur,rdr+1):
			rset.add(dmap[r][luc-1])
	if rdr < n-1:
		for c in range(luc,rdc+1):
			rset.add(dmap[rdr+1][c])
	if rdc < m-1:
		for r in range(lur,rdr+1):
			rset.add(dmap[r][rdc+1])

	if '.' in rset:
		rset.remove('.')
	print(len(rset))