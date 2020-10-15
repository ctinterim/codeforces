import sys

if __name__ == '__main__':
	i = int(input())
	if (i & 1 == 0) and (i >= 4):
		print("YES")
	else:
		print("NO")