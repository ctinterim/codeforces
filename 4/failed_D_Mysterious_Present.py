if __name__ == '__main__':
	N, ew, eh = tuple(map(int,input().split()))
	env = []
	for i in range(N):
		w, h = tuple(map(int,input().split()))
		if (w > ew) and (h > eh):
			env.append((i+1, w, h))

	env.sort(key=lambda t:t[1]*t[2])

	chains = []
	while True:
		if len(env) == 0:
			break

		fi, fw, fh = env[0]
		emi, emw, emh = env[-1]

		if (emw > fw) and (emh > fh):
			chain = [env[0]]
			left = []
			for i in range(1,len(env)):
				maxi, maxw, maxh = chain[-1]
				curi, curw, curh = env[i]

				if (curw > maxw) and (curh > maxh):
					chain.append(env[i])
				else:
					left.append(env[i])

			chains.append(chain)
			env = left
		else:
			chains.append([env[0]])
			env = env[1:]

	if len(chains) > 0:
		chains.sort(key=lambda c:len(c), reverse=True)
		print(len(chains[0]))
		print(' '.join([str(chains[0][i][0]) for i in range(len(chains[0]))]))
	else:
		print(0)