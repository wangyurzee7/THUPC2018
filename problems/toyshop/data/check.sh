cp ../wyz/force.cpp force.cpp
g++ force.cpp -o force -O2 -std=c++11
for ((i=1;;++i))
do
	if [ ! -e $i.in ]
	then
		break
	fi
	time ./force <$i.in >output.out
	if diff output.out $i.ans >difflog
	then
		echo Testcase#$i Accepted
	else
		echo Testcase#$i WrongAnswer!!!!!!!!
		exit
	fi
done
rm force force.cpp output.out
