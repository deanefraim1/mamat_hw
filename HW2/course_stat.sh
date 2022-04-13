#!/bin/bash

# check if the argument is a valid course number
if ( [[ $# -ne 1 ]] || [[ ! $1 =~ ^[0-9]+$ ]] ); then
	echo "Wrong number of arguments" >&2
	exit 1
fi

if [[ ! -f "$1.txt" ]]; then
	echo "Course not found" >&2
	exit 1
fi

if [[ -d "$1_stat" ]]; then
	rm -r "$1_stat"
fi

mkdir "$1_stat"

cut -d $'\t' -f 2 $1.txt > $1_stat/grades.txt

sed -i '' '1d' $1_stat/grades.txt

gcc -c -g -Wall calc_statistics.c

gcc -o prog.exe calc_statistics.o

./prog.exe "$1_stat/course_statistics.txt" "$1_stat/grades.txt"

cd "$1_stat"

cat course_statistics.txt

cd ../

rm calc_statistics.o
