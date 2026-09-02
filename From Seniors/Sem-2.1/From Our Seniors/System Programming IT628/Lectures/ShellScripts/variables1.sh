local_var=1
echo "Process variables1.sh has local_var value = $local_var"
env_var=2
export env_var
echo "Process variables1.sh has env_var value = $env_var"
./variables2.sh