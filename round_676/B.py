if __name__ == '__main__':
	t = int(input())
	for i in range(t):
		n = int(input())
		matrix = [input() for j in range(n)]

		#        (1,2)           (2,1)           (n,n-1)            (n-1,n)
		val = matrix[0][1] + matrix[1][0] + matrix[n-1][n-2] + matrix[n-2][n-1]

		answer = {
			'0000' : [(1,2),(2,1)],
			'0001' : [(n,n-1)],
			'0010' : [(n-1,n)],
			'0011' : [],
			'0100' : [(1,2)],
			'0101' : [(1,2), (n-1,n)],
			'0110' : [(2,1), (n-1,n)],
			'0111' : [(2,1)],
			'1000' : [(2,1)],
			'1001' : [(2,1), (n-1,n)],
			'1010' : [(2,1), (n,n-1)],
			'1011' : [(1,2)],
			'1100' : [],
			'1101' : [(n-1,n)],
			'1110' : [(n,n-1)],
			'1111' : [(1,2),(2,1)],
		}

		
		answer_t = answer[val]
		print(len(answer_t))
		for r,c in answer_t:
			print('{} {}'.format(r,c))