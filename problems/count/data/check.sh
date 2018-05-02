cp ../FoolMike/Mike_n2logn.cpp std.cpp
g++ std.cpp -o std -O2 -std=c++11
for ((i=1;;++i))
do
	if [ ! -e $i.in ]
	then
		break
	fi
	time ./std <$i.in >output.out
	if diff $i.ans output.out
	then
		echo AC!
	else
		echo WrongAnswer!!!!!!!!!!
	fi
done
rm std std.cpp output.out
