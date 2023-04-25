#!/bin/bash
#Szeri Jozsef

if [[ $# -lt 2 ]]
then
	echo "Tul keves parameter! Hasznalat: parancs NAP FELHASZNALOK..."
	exit 1
fi

if [[ ! $1 =~ ^[0-9]+$ ]]
then
	echo "Az elso parameternek SZAMNAK kell lennie!"
	exit 1
fi

datum="$1"

for user in "${@:2}"
do
	if id $user > /dev/null 2>&1
	then
		if last $user | grep -q "$(date +%b\ $datum)"
		then
			echo "[$user] - dolgozott"
		else
			echo "[$user] - nem dolgozott"
		fi
	else
		echo "[$user] - nem letezik"
	fi
done
