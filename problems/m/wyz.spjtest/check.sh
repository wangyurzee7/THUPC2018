expected=$(cat $1.score)
make chk
./chk $1.in $1.out $1.ans fullScore.txt result.txt
if (($? && expected == 1))
then
	echo SPJ Boooooooooooomed!!!!!
	exit 2
fi
i=0
while read line
do
	((++i))
	if ((i == 1))
	then
		score=$line
	fi
	if ((i == 2))
	then
		info=$line
	fi
done <result.txt
echo score : ${score}  \( expected: ${expected} \)
echo info : ${info}
if ((score == expected))
then
	echo Correct Judgement!
else
	echo Wrong Judgement...
	exit 1
fi
rm result.txt
