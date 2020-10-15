if __name__ == '__main__':
	Y,W = tuple(map(int, input().split()))
	M = max(Y,W)

	answers = {
		1:'1/1',
		2:'5/6',
		3:'2/3',
		4:'1/2',
		5:'1/3',
		6:'1/6'
	}

	print(answers[M])