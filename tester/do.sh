#!/bin/bash

source ./fct.sh

containers=(vector stack map)
if [ $# -ne 0 ]; then
	containers=($@);
fi
for container in ${containers[@]}; do
	printf "%40s\n\n" $container
	do_test $container 2>/dev/null
	printf "\n"
done;
