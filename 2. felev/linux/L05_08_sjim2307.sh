#!/bin/bash
#Szeri Jozsef

if [[ $# -eq 0 ]]
then
	echo "Adjon meg legalabb egy fajlt!"
	exit 1
fi

for file in "$@"
do
	if [[ ! -f "$file" ]]
	then
		echo "[$file] nem letezik az allomany"
		continue
	fi
	
	sed -i 's/\([^:]*\):\([^:]*\):\([^:]*\)/\3:\2:\1/g' "$file"
	
	echo "[$file] modositottuk"
done
