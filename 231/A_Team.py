if __name__ == '__main__':
  numprob = int(input())
  numsolv = 0
  for i in range(numprob):
    iline = list(map(int, input().strip().split()))
    if iline.count(1) >= 2:
      numsolv += 1
  print(numsolv)