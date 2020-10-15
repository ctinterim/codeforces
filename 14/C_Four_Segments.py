if __name__ == '__main__':
	segments = []
	for i in range(4):
		segments.append(tuple(map(int,input().split())))

	for i in range(len(segments)):
		x1,y1,x2,y2 = segments[i]
		if x2 < x1:
			segments[i] = (x2,y2,x1,y1)
		if y2 < y1:
			segments[i] = (x2,y2,x1,y1)

	if len(set(segments)) != 4:
		print('NO')
		exit()

	for i in range(4):
		x1,y1,x2,y2 = segments[i]
		# check degenerate segments
		if (x1 == x2) and (y1 == y2):
			print('NO')
			exit()
		# check whether segments parallel to any coordinate axis
		if (x1 != x2) and (y1 != y2):
			print('NO')
			exit()

	# check the number of points
	pointset = set([])
	for x1,y1,x2,y2 in segments:
		pointset.add((x1,y1))
		pointset.add((x2,y2))

	if len(pointset) == 4:
		pointlist = list(pointset)
		xlist = [p[0] for p in pointset]
		ylist = [p[1] for p in pointset]

		if len(set(xlist)) != 2 or len(set(ylist)) != 2:
			print('NO')
			exit()
			
		print('YES')
	else:
		print('NO')