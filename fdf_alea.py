#!/bin/python3
import sys
import random

x,y = list(map(int, sys.argv[1:]))[:2]
tab = [[0]*(x)]
for k in range(y - 1):
	tab.append([0])
	for j in range(x-1):
		a,b = sorted([tab[k-1][j], tab[k][j-1]])
		tab[-1].append(random.randint(a-5, b+5))

for ligne in tab:
	for i,point in enumerate(ligne):
		print(f'{point},0x{"ff" if point > 5 else "00"}{"ff" if point > 10 else "00"}{"ff"}', end=" "*(len(ligne)-1 != i))
	print("")