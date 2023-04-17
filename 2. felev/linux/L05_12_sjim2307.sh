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
	
	sed -i -E 's/(^|[^[:digit:]])1([^[:digit:]]|$)/\1egy\2/g' "$file"
	sed -i -E 's/(^|[^[:digit:]])2([^[:digit:]]|$)/\1ketto\2/g' "$file"
	sed -i -E 's/(^|[^[:digit:]])3([^[:digit:]]|$)/\1harom\2/g' "$file"
	sed -i -E 's/(^|[^[:digit:]])4([^[:digit:]]|$)/\1negy\2/g' "$file"
	sed -i -E 's/(^|[^[:digit:]])5([^[:digit:]]|$)/\1ot\2/g' "$file"
	sed -i -E 's/(^|[^[:digit:]])6([^[:digit:]]|$)/\1hat\2/g' "$file"
	sed -i -E 's/(^|[^[:digit:]])7([^[:digit:]]|$)/\1het\2/g' "$file"
	sed -i -E 's/(^|[^[:digit:]])8([^[:digit:]]|$)/\1nyolc\2/g' "$file"
	sed -i -E 's/(^|[^[:digit:]])9([^[:digit:]]|$)/\1kilenc\2/g' "$file"
	
	echo "[$file] modositottuk"
done
