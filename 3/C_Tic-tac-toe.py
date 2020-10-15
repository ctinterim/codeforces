def checkTurn(state):
	numX, num0 = 0,0
	for x in range(3):
		numX += state[x].count('X')
		num0 += state[x].count('0')

	if numX == num0:
		turn = 'first'
	elif numX == (num0 + 1):
		turn = 'second'
	else:
		turn = 'illegal'

	if (turn != 'illegal') and (numX + num0 == 9):
		turn = 'draw'

	return numX, num0, turn

def checkResult(state, char):
	allchar = [char,char,char]
	numwin = 0
	# check horizontal
	for x in range(3):
		hline = [state[x][i] for i in range(3)]
		if hline == allchar:
			numwin += 1
	# check vertical
	for y in range(3):
		vline = [state[i][y] for i in range(3)]
		if vline == allchar:
			numwin += 1
	# check diagonal
	diagR = [state[i][i] for i in range(3)]
	diagV = [state[i][2-i] for i in range(3)]
	if diagR == allchar:
		numwin += 1
	if diagV == allchar:
		numwin += 1

	return numwin

if __name__ == '__main__':
	state = [input() for i in range(3)]

	numX, num0, turn = checkTurn(state)
	
	if turn == 'illegal':
		print('illegal')
		exit()

	winX = checkResult(state, 'X')
	win0 = checkResult(state, '0')

	if winX > 0 and win0 > 0:
		verdict = 'illegal'
	elif winX > 0 and num0 >= numX:
		verdict = 'illegal'
	elif win0 > 0 and numX > num0:
		verdict = 'illegal'
	elif winX > 0:
		verdict = 'the first player won'
	elif win0 > 0:
		verdict = 'the second player won'
	else:
		verdict = turn

	print(verdict)