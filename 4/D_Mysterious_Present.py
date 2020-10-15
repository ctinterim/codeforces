from collections import namedtuple

Node = namedtuple('Node', 'i w h area')

FORMER_INDEX = 0
CHAIN_COUNT = 1

if __name__ == '__main__':
	N, ew, eh = tuple(map(int,input().split()))
	env = []
	for i in range(N):
		w, h = tuple(map(int,input().split()))
		if (w > ew) and (h > eh):
			env.append([-1, 1, Node(i+1, w, h, w*h)])

	if len(env) == 0:
		print(0)
		exit()

	env.sort(key=lambda t:t[2].area)
	minchild = env[0][2]
	for i in range(1, len(env)):
		curr = env[i][2]
		maxj = -1
		maxcount = -1
		for j in range(i-1, -1, -1):
			child = env[j][2]
			child_chaincount = env[j][CHAIN_COUNT]
			if (curr.w > child.w) and (curr.h > child.h) and (child_chaincount > maxcount):
				maxj = j
				maxcount = child_chaincount

		if maxj >= 0:
			env[i][FORMER_INDEX] = maxj
			env[i][CHAIN_COUNT] += maxcount


	maxcount = 0
	maxidx = -1
	for i in range(len(env)):
		if env[i][CHAIN_COUNT] > maxcount:
			maxcount = env[i][CHAIN_COUNT]
			maxidx = i

	chain = [maxidx]
	nextidx = env[maxidx][FORMER_INDEX]
	while nextidx >= 0:
		curridx = nextidx
		chain.append(curridx)
		nextidx = env[curridx][FORMER_INDEX]

	print(maxcount)
	print(' '.join([str(env[e][2].i) for e in chain[::-1]]))