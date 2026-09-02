#!/bin/bash

for_test()
{
	for var in var1 var2 var3
	do
		echo $var
	done
}

select_test()
{
	select var in opt1 opt2 opt3
	do
		
		case $var in
			opt1) echo "opt1 is selected";;
			opt2) echo "opt2 is selected";;
			opt3) echo "opt3 is selected";;
			none) break;;
			*) echo "incorrect option";;
			esac
		
		echo "$var is selected"
	done
	echo "just print"
}

#for_test
select_test
