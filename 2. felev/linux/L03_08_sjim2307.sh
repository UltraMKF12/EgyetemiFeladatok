#!/bin/bash

# Széri József

# ~sjim2307/public_html lehet megneznisd
# who | head | cut -f 2 -d "(" | cut -f1 -d ")"
# who | head | cut -f 1 -d " "

if [[ $# -ge 2 ]]
then
	echo "Helytelen parameter szam!"
	echo "Helyes hasznalat: $0 [-v]"
	exit 1
fi

who | while read line
do
	username=$(echo $line | cut -f 1 -d " ")
	hostname=$(echo $line | cut -f 2 -d "(" | cut -f1 -d ")")
	if [[ $1 == "-v" ]]
	then
		website="nincs"
		homedir=$( getent passwd $username | cut -d: -f6 )
		if [[ -d $homedir/public_html ]]
		then
			if [[ `stat -c "%A" $homedir/public_html` == d??????r?? ]]
			then
				website="van"
			fi
		fi

		echo "$username $hostname $website"
	else
		echo "$username $hostname"
	fi
done
