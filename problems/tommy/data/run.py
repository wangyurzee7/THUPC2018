from os import *
system("pypy mkr.py 234567 1 > 1.in")
system("pypy mkr.py 234567 100 > 2.in")
system("pypy mkr.py 234567 1000 > 3.in")
system("pypy mkr.py 234567 5000 > 4.in")
system("pypy mkr.py 234567 10000 >5.in")
system("pypy mkr.py 234567 20000 > 6.in")
system("pypy mkr.py 234567 30000 > 7.in")
system("pypy mkr.py 234567 50000 > 8.in")
system("pypy mkr.py 234567 80000 > 9.in")
system("pypy mkr.py 234567 100000 >10.in")
system("pypy mkr.py 234567 150000 > 11.in")
system("pypy mkr.py 234567 200000 > 12.in")
system("pypy mkr.py 234567 230000 > 13.in")
system("pypy mkr.py 234567 234000 > 14.in")
system("pypy mkr.py 234567 234567 > 15.in")

system("g++ ../immortalCO/tmp.cpp -o tmp -O2 -std=c++11")
for i in xrange(1,16):
	print i
	system("/usr/bin/time ./tmp < %d.in > %d.ans" % (i,i))