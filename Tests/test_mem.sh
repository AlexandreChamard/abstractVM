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

prog=$1
shift
verbose=false

if [[ $# -ge 1 && $1 == '-v' ]]
then
	verbose=true
	shift
fi
if [[ $# -eq 0 ]]
then
	for f in $(find . -name \*.svm -print)
	do
		if [[ $f == *"err"* ]]
		then
			printf '\e[1;31m%s\e[m\n' "$f"
		else
			printf '\e[1;34m%s\e[m\n' "$f"
		fi
		if [[ $verbose == true ]]
		then
			cat $f
			echo -e '\n--------'
		fi
		valgrind --leak-check=full ./$prog $f 1>/dev/null
	done
else
	while [[ $# -gt 0 ]]
	do
		if [[ $1 == *"err"* ]]
		then
			printf '\e[1;31m%s\e[m\n' "$1"
		else
			printf '\e[1;34m%s\e[m\n' "$1"
		fi
		if [[ $verbose == true ]]
		then
			cat $1
			echo -e '\n--------'
		fi
		valgrind --leak-check=full ./$prog ./$1 1>/dev/null
		./$prog ./$1
		shift
	done
fi
