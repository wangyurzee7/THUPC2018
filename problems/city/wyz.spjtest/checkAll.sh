buffer=""
for ((i=1;;++i))
do
	if [ ! -e $i.score ]
	then
		break
	fi
	echo [ Case\#$i ]:
	./check.sh $i
	if (($?))
	then
		read -s -n1 -p "Press any key to continue..."
		buffer+=$i' '
	fi
	echo ''
done
echo \[Wrong Case Id\]: $buffer
