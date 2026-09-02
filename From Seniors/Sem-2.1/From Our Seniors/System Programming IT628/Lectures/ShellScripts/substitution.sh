#!/bin/bash
echo "\tnot substituted tab"
echo -e "\tsubstituted tab"

DATE=`date`
echo "today is: $DATE"

echo "var is set to 1"
var=1
echo "var=${var}"
echo "var=${var:-0}"
echo "var=${var:?Data not available}"
echo "var=${var:=0} var=${var}"

echo "var is set to No Value"
var=
echo "var=${var}"
echo "var=${var:-0}"
echo "var=${var:?Data not available}"
echo "var=${var:=0}"

