# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    do.sh                                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 16:52:26 by acoezard          #+#    #+#              #
#    Updated: 2022/04/05 16:52:28 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
