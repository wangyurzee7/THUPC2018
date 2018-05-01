cp ../613/std.cpp std.cpp
make std
for ((i=1;;++i))
do
	if [ ! -e $i.in ]
	then
		break
	fi
	time ./std <$i.in >$i.ans
done
rm std std.cpp
