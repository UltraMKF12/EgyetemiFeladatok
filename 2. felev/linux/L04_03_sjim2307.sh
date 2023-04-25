#!/bin/bash
#Szeri Jozsef

if [[ $# -lt 1 ]]
then
	echo "Szukseges legalabb 1 parameter: parancs DIRECTORY..."
	exit 1
fi

for directory in "$@"
do
	if [[ ! -d "$directory" ]] || [[ ! -r "$directory" ]]
	then
		echo "A megadott nev nem mappa, vagy nem olvashato $directory"
		continue
	fi

	find $directory -type f -printf "%p\n" | while read line
	do
		jogok=$(ls -l $line | grep -E -o '[drwx-]{10}')
		echo "$line $jogok"
	done
done
