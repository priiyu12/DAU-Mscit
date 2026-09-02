#!/bin/bash
echo $#
i=1
sum=0
while [ $i -le $# ]
do
	sum=`expr $sum + $i`
	i=`expr $i + 1`
done
echo $sum

