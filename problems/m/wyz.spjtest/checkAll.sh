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
		exit 1
	fi
	echo ''
done

