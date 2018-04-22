from random import *
T = 9999
f = open('../data/1.in','w')
f.write(str(T)+'\n')
for i in range(T):
	ss = ''
	if randint(1,8) == 1:
		ss += '1'
	else:
		ss += str(randint(1,99999))
	ss += ' '
	if randint(1,7) == 1:
		ss += '1'
	else:
		ss += str(randint(1,99999))
	ss += ' '
	if randint(1,6) == 1:
		ss += '1'
	else:
		ss += str(randint(1,99999))
	ss += ' '
	if randint(1,5) == 1:
		ss += '1'
	else:
		ss += str(randint(1,99999))
	ss += '\n'
	f.write(ss)
f.close()
