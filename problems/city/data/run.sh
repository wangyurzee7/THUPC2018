for ((i=1;i<=100;i++))
do
	echo "case$i:"
	./chk.exe $i.in $i.out $i.ans $i.score
	sleep 0.1
done
