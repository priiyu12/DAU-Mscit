cat foo.txt

# redirect stdout to output.txt file
cat foo.txt > output.txt
cat output.txt

# redirect stdout to output.txt file
cat nop.txt > output.txt

# redirect stdout to output.txt file
cat foo.txt 1> output.txt
# redirect stderr to output.txt file
cat foo.txt 2> error.txt

cat nop.txt 1> output.txt
cat nop.txt 2> error.txt

# stderr merged with stdout and redirected both to output.txt file
cat foo.txt > output.txt 2>&1

cat nop.txt > output.txt 2>&1