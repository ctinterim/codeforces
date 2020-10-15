if __name__ == '__main__':
	n = int(input())
	score = {}
	data = []
 
	for i in range(n):
		name, ns = input().split()
		ns = int(ns)
		data.append((name,ns))
		if name not in score:
			score[name] = ns #current score / maxscore i
		else:
			score[name] += ns
			
	maxscore = -9999
	for name in score:
		if score[name] > maxscore:
			maxscore = score[name]
 
	checkscore = {name:0 for name in score}
	maxname = None
	for name, ns in data:
		checkscore[name] += ns
		if (checkscore[name] >= maxscore) and (score[name] == maxscore):
			maxname = name
			break 
 
	print(maxname)