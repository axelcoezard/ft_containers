# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    fct.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 16:52:33 by acoezard          #+#    #+#              #
#    Updated: 2022/04/05 16:53:10 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

EOC="\e[0m"
BOLD="\e[1m"
RED="\e[91m"
GREEN="\e[92m"
YELLOW="\e[93m"
DBLUE="\e[94m"
PURPLE="\e[95m"
CYAN="\e[96m"
DGREY="\e[1;90m"

incl_path="../includes"
srcs="srcs"

CC="clang++"
CFLAGS="-Wall -Wextra -Werror -std=c++98"

compile () {
	macro_name=$(echo "USING_${2}" | awk '{ print toupper($0) }')
	compile_cmd="$CC $CFLAGS -o ${3} -I./$incl_path -D ${macro_name} ${1}"
	if [ -n "$4" ]; then
		compile_cmd+=" &>${4}"
	fi
	eval "${compile_cmd}"
	return $?
}

getEmoji () {
	# 1=integer
	emoji='';
	case $1 in
		0) emoji="${GREEN}✅";;
		1) emoji="${RED}❌";;
		2) emoji="${YELLOW}⚠️ ";;
	esac
	printf "${BOLD}${emoji}${EOC}"
}

getYN () {
	res='';
	case $1 in
		0) res="Y";;
		1) res="N";;
	esac
	printf "${res}"
}

getTime () {
	printf "%#3d%%" $1
}

printRes () {
	printf "%-35s: COMPILE: %s | RET: %s | OUT: %s | EFFICIENCY: %s\n" \
		"$1" "$(getEmoji $2)" "$(getEmoji $3)" "$(getEmoji $4)" "$(getTime $6)"
}

compare_output () {
	# 1=diff_file
	if ! [ -s $1 ]; then
		return 0
	fi
	regex=$(cat <<- EOF
	^[0-9]*c[0-9]*
	< max_size: [0-9]*
	---
	> max_size: [0-9]*$
	EOF
	)

	cat $1 | grep -v -E -q "$regex"
	[ "$?" -eq "0" ] && return 1 || return 2;
}

isEq () {
	[ $1 -eq $2 ] && echo 0 || echo 1
}

getMillis () {
	python -c 'import time; print(int(time.time() * 1000))'
}

cmp_one () {
	deepdir="deepthought"; logdir="logs"
	mkdir -p $deepdir $logdir
	container=$(echo $1 | cut -d "/" -f 2)
	file=$(echo $1 | cut -d "/" -f 3)
	testname=$(echo $file | cut -d "." -f 1)
	ft_bin="ft.$container.out"; ft_log="$logdir/ft.$testname.$container.log"
	std_bin="std.$container.out"; std_log="$logdir/std.$testname.$container.log"
	diff_file="$deepdir/$testname.$container.diff"

	clean_trailing_files () {
		rm -f $ft_bin $std_bin
		[ -s "$diff_file" ] || rm -f $diff_file $ft_log $std_log &>/dev/null
		rmdir $deepdir $logdir &>/dev/null
	}

	compile "$1" "ft"  "$ft_bin"  /dev/null; ft_ret=$?
	compile "$1" "std" "$std_bin" /dev/null; std_ret=$?
	same_compilation=$(isEq $ft_ret $std_ret)
	std_compile=$std_ret

	> $ft_log; > $std_log;
	start_ft=$(getMillis)
	if [ $ft_ret -eq 0 ]; then
		./$ft_bin &>$ft_log; ft_ret=$?
	fi
	end_ft=$(getMillis)
	start_std=$(getMillis)
	if [ $std_ret -eq 0 ]; then
		./$std_bin &>$std_log; std_ret=$?
	fi
	end_std=$(getMillis)

	ft_time=$(echo "$end_ft - $start_ft" | bc)
	std_time=$(echo "$end_std - $start_std" | bc)
	runtime_ratio=$(((std_time - ft_time) * 100 / std_time))

	same_bin=$(isEq $ft_ret $std_ret)
	diff $std_log $ft_log 2>/dev/null 1>"$diff_file";
	compare_output $diff_file
	same_output=$?

	printRes "$container/$file" $same_compilation $same_bin $same_output $std_compile $runtime_ratio
	clean_trailing_files
}

do_test () {
	test_files=$(find "${srcs}/${1}" -type f -name '*.cpp' | sort)
	for file in ${test_files[@]}; do
		cmp_one "${file}"
	done
}
