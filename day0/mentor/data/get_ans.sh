g++ ../wyz/std.cpp -o std -std=c++11
for ((i=1;i<=10;++i))
do
	time ./std <$i.in >$i.ans
done
