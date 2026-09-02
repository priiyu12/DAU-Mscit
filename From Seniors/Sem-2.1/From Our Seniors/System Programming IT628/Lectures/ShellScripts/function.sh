#!/bin/bash
# Define your function here 
Hello () { 
	if [ $# > 1 ]
	then
	  for param in $*
	  do
	    echo $param
	  done
	fi
	return 10
} 
# Invoke your function 
Hello $*
# Capture value returnd by last command
ret=$? 
echo "Return value is $ret"
