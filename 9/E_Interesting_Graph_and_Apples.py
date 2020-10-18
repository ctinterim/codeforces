def dfs(v, graph):
	isloop = False
	lo, ro = graph

	# expand right
	pr, r = lo, ro
	expand_right = []
	while True:
		if len(v[r]) == 1:
			break
		else:
			nr1, nr2 = v[r]
			rn = nr1 if nr1 != pr else nr2
			expand_right.append(rn)
			if rn == lo: # we found loop
				isloop = True
				break
			pr = r
			r = rn

	if isloop:
		return True, graph + expand_right

	# expand left
	l, pl = lo, ro
	expand_left = []
	while True:
		if len(v[l]) == 1:
			break
		else:
			nl1, nl2 = v[l]
			nl = nl1 if nl1 != pl else nl2
			expand_left.append(nl)
			pl = l
			l = nl

	final_graph = expand_left[::-1] + graph + expand_right
	# if final_graph[0] > final_graph[-1]:
	# 	final_graph = final_graph[::-1]

	return False, final_graph

def findMinvalInLineEnds(lines):
	minval, minval_idx = 0xFFFF, None
	secval, secval_idx = 0xFFFF, None

	for i in range(len(lines)):
		if lines[i][0] < minval:
			secval = minval
			secval_idx = minval_idx
			minval = lines[i][0]
			minval_idx = i
		elif lines[i][0] < secval:
			secval = lines[i][0]
			secval_idx = i

	return minval, minval_idx, secval, secval_idx

def greedyConnect(lines, points):
	edges = []
	points.sort()

	if len(points) == 1 and len(lines) == 0:
		edges.append((points[0],points[0]))
		return edges

	while True:
		if len(lines) == 1 and len(points) == 0:
			edges.append((lines[0][0], lines[0][-1]))
			break

		minval_p = points[0] if len(points) > 0 else 0xFFFF
		secval_p = points[1] if len(points) > 1 else 0xFFFF
		minval_l, minval_idx_l, secval_l, secval_idx_l = findMinvalInLineEnds(lines)

		if minval_p < minval_l:
			if secval_p < minval_l: # connect 2 points to make a line
				edges.append((minval_p, secval_p))
				points = points[2:]
				lines.append([minval_p, secval_p])
			else: # connect point to the line
				edges.append((minval_p, minval_l))
				li = minval_idx_l
				lines[li] = [minval_p, lines[li][-1]]
				points = points[1:]
		else:
			# if minval is one end of line, we merge that line with a point or a line
			if minval_p < secval_l:
				edges.append((minval_l, minval_p))
				li = minval_idx_l
				lines[li][0] = minval_p
				if lines[li][0] > lines[li][-1]:
					lines[li] = [lines[li][-1], lines[li][0]]
				points = points[1:]
			else:
				edges.append((minval_l, secval_l))
				mil, sil = minval_idx_l, secval_idx_l
				lines[mil][0] = lines[sil][-1]
				if lines[mil][0] > lines[mil][-1]:
					lines[mil] = [lines[mil][-1], lines[mil][0]]
				del lines[sil]
	return edges

if __name__ == '__main__':
	n,m = tuple(map(int, input().split()))
	v = [[] for i in range(n)]

	for i in range(m):
		v1,v2 = tuple(map(int, input().split()))
		v1,v2 = v1-1,v2-1
		v[v1].append(v2)
		v[v2].append(v1)

	# validate input
	input_valid = True
	for i in range(n):
		if len(v[i]) > 2:
			input_valid = False
			break
		v[i].sort()

	if not input_valid:
		print('NO')
		exit()

	loops = []
	lines = []
	points = []

	visited = [False for i in range(n)]

	for i in range(n):
		if visited[i]:
			continue
		elif len(v[i]) == 0:
			points.append(i)
			visited[i] = True
		elif len(v[i]) == 1 and v[i] == i:
			loops.append([i,i])
			visited[i] = True
		else:
			isloop, graph = dfs(v,[i,v[i][0]])
			for gi in graph:
				visited[gi] = True
			if isloop:
				loops.append(graph)
			else:
				lines.append(graph)

	if len(loops) > 0:
		if len(loops) == 1 and len(points) == 0 and len(lines) == 0:
			print('YES')
			print(0)
			exit()
		else:
			print('NO')
			exit()

	# print('loops')
	# for p in loops:
	# 	print('\t{}'.format([e+1 for e in p]))
	# print('lines')
	# for p in lines:
	# 	print('\t{}'.format([e+1 for e in p]))
	# print('points')
	# for p in points:
	# 	print('\t{}'.format(p+1))

	# We only need two ends of the line
	for li in range(len(lines)):
		e1,e2 = lines[li][0], lines[li][-1]
		lines[li] = [e1,e2] if e1<e2 else [e2,e1]

	edges = greedyConnect(lines, points)

	print('YES')
	print(len(edges))
	for v1,v2 in edges:
		v1 += 1
		v2 += 1
		if v1 < v2:
			print('{} {}'.format(v1,v2))
		else:
			print('{} {}'.format(v2,v1))