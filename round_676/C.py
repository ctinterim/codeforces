def L(s, k):
	return s[1:k][::-1] + s

def R(s,k):
	return s + s[k:-1][::-1]

if __name__ == '__main__':
	s = input()
	print(3)

	# Do R N-1
	print('R {}'.format(len(s)-1))
	s = R(s, len(s)-2)

	# DO L N-1
	print('L {}'.format(len(s)-1))
	s = L(s, len(s)-1)

	# DO L 2
	print('L {}'.format(2))
	s = L(s, 2)