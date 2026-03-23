#!/bin/sh
# Author: Matija Jevtic

if [ $# -lt 2 ]
then
	echo "Two parameters should be provided!"
	exit 1
fi

FILESDIR=$1
SEARCHSTR=$2

if [ -d $FILESDIR ]
then
	echo "Directory exists!"
else
	echo "Directory doesn't exist!"
	exit 1
fi

num_of_files=$(find "$FILESDIR" -type f | wc -l)
num_of_findings=$(grep -r "$SEARCHSTR" "$FILESDIR" | wc -l)

echo "The number of files are $num_of_files and the number of matching lines are $num_of_findings"
