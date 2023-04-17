#!/bin/bash
#Szeri Jozsef

if [[ $# -lt 2 ]]
then
	echo "Adj meg egy szot egy legalabb egy allomany: parancs szo allomanyok..."
	exit 1
fi

for file in "${@:2}"
do
	if [[ ! -f "$file" ]]
	then
		echo "[$file] nem letezik az allomany"
		continue
	fi
	
	sed -i "s/[a-z]/$1&/g" "$file"
	
	echo "[$file] modositottuk"
done
