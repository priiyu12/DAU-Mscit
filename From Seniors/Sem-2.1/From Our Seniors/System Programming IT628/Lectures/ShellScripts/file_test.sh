#!/bin/bash
testfile=test.sh
if [ -e $testfile ]
then
	echo "file exists"
else
	echo "file does not exists"
fi

