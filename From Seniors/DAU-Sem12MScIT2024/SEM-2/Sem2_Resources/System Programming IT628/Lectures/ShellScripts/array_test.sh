#!/bin/bash

#<< --MultilineComment--
NAME[0]="First"
NAME[1]="Second"
NAME[2]="3"
NAME[3]="Forth"
NAME[4]="5"
#--MultilineComment--

#NAME=("First", "Second", "Third", "Forth", "Fifth")
echo "First Index: ${NAME[0]}"
echo "Second Index: ${NAME[1]}"

echo "All Index: ${NAME[*]}"
echo "All Index: ${NAME[@]}"

echo ${#NAME[*]}
