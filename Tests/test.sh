#!/bin/bash

if [[ $# == 0 ]]
then
	echo -e "\n\tUSAGE :  "$0" ./your_prog [-v | testfile]\n"
	exit
fi
if [[ ! -f $1 ]]
then
	echo $1" : file not found"
	exit 1
fi

if [[ $# != 1 && $2 != '-v' ]]
then
	printf '\e[1;34m%s\e[m\n' "$2"
	if [[ $3 == -v ]]
	then
		cat $2
		echo -e '\n--------'
	fi
	./$1 ./$2
	exit
fi

for f in $(find . -name \*.svm -print)
do
	printf '\e[1;34m%s\e[m\n' "$f"
	if [[ $2 == -v ]]
	then
		cat $f
		echo -e '\n--------'
	fi
	./$1 $f
done