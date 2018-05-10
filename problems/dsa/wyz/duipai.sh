make gen
for ((i=1;;++i))
do
	SEED=$((RANDOM*32768+RANDOM))
	echo ${SEED} >seed.txt
	./gen ${SEED} 6 266 266 100000000 >input.in
	./std <input.in >output.ans
	./wyz <input.in >output.out
	if diff output.out output.ans >difflog.txt
	then
		echo AC
	else
		echo WA!!!!!
		break
	fi
done
