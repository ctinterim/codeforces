from sys import stdin
 
if __name__ == '__main__':
	users = set([])
	traffic = 0
 
	for line in stdin:
		line = line.strip()
		if line[0] == '+':
			users.add(line[1:])
		elif line[0] == '-':
			users.remove(line[1:])
		else:
			content = line[line.find(':')+1:]
			traffic += len(users)*len(content)
 
	print(traffic)