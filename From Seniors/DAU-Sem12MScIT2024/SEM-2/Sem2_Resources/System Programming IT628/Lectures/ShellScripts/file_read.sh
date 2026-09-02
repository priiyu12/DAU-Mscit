#!/bin/bash
testfile=test.sh
if [ -e $testfile ]
then
	while read p; 
	do
		echo "Line:$p"
	done < $testfile
fi
