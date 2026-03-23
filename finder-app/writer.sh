#!/bin/sh
# Author: Matija Jevtic

if [ $# -lt 2 ]
then
	echo "Two parameters should be provided!"
	exit 1
fi

WRITEFILE=$1
WRITESTR=$2
DIR=$(dirname $WRITEFILE)

mkdir -p $DIR

touch $WRITEFILE || { echo "File is not created!"; exit 1; }

echo "$WRITESTR" >> "$WRITEFILE"
