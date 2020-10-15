def determine(l,a,b):
	if l < a+b:
		return 'TRIANGLE'
	elif l == a+b:
		return 'SEGMENT'
	else:
		return 'IMPOSSIBLE'
 
 
if __name__ == '__main__':
	lines = list(map(int, input().split()))
	lines.sort(reverse=True)
	
	result = set([determine(*lines[:-1]), determine(*lines[1:])])
 
	if 'TRIANGLE' in result:
		print('TRIANGLE')
	elif 'SEGMENT' in result:
		print('SEGMENT')
	else:
		print('IMPOSSIBLE')