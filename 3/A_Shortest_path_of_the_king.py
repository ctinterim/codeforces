def toCoord(line):
	return ord('a')-ord(line[0]), ord('1')-ord(line[1])

if __name__ == '__main__':
	kx, ky = toCoord(input())
	tx, ty = toCoord(input())

	moves = []

	# do diagnoal move first if necessary
	lr = 'L' if (kx < tx) else 'R'
	ud = 'D' if (ky < ty) else 'U'

	if (kx != tx) and (ky != ty):
		if abs(kx-tx) < abs(ky-ty):
			diag = abs(kx-tx)
			parallel = abs(ky-ty) - diag
			last = ud
		else:
			diag = abs(ky-ty)
			parallel = abs(kx-tx) - diag
			last = lr

		for i in range(diag):
			moves.append(lr+ud)
		for i in range(parallel):
			moves.append(last)
	else:
		if kx == tx:
			for i in range(abs(ky-ty)):
				moves.append(ud)
		else:
			for i in range(abs(kx-tx)):
				moves.append(lr)

	print(len(moves))
	print('\n'.join(moves))