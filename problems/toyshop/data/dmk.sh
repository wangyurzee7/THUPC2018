make gen
if [ -e seed.txt ]
then
	./gen $(cat seed.txt)
else
	./gen
fi
