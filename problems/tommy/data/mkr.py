from os import *
from sys import *
from random import *

N = int(argv[1])
L = int(argv[2])

P = range(1,N+1)
shuffle(P)
P = [0] + P

print N, P[1], P[L]
E = []
for i in xrange(1, L):
	E.append([P[i], P[i + 1]])

SS = []

for i in xrange(max(1, int(N / 1000))):
	SS.append(randint(1, L))

for i in xrange(L + 1, N + 1):
	if randint(1, 5) == 1:
		f = SS[randint(0, len(SS) - 1)]
	else:
		f = randint(1, i - 1)
	assert 1 <= f < i
	E.append([P[f], P[i]])
	if randint(1, 1000) == 1:
		SS.append(i)

shuffle(E)
for e in E:
	shuffle(e)
	print e[0], e[1]