cp ../wyz/std.cpp std.cpp
g++ std.cpp -o std -O2 -std=c++11
for ((i=1;i<=4;++i))
do
	time ./std <$i.in >$i.ans
done
rm std.cpp std
