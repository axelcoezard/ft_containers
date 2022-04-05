# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 10:40:18 by acoezard          #+#    #+#              #
#    Updated: 2022/04/05 16:52:13 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	ft_containers
ARCH	:=	x64

# -----------------------------------------------------------------------------
# COMPILATION
# -----------------------------------------------------------------------------
SRCS	:=	main.cpp
OBJS	:=	$(addprefix bin/, $(SRCS:.cpp=.o))

CC		:=	clang++
CFLAGS	:=	-Wall -Wextra -Werror -std=c++98

# -----------------------------------------------------------------------------
# COLORS
# -----------------------------------------------------------------------------
__RED		:=	"\033[1;31m"
__GREEN		:=	"\033[1;32m"
__YELLOW	:=	"\033[1;33m"
__BLUE		:=	"\033[1;36m"
__WHITE		:=	"\033[1;37m"
__EOC		:=	"\033[0;0m"

# -----------------------------------------------------------------------------
# RULES
# -----------------------------------------------------------------------------
bin/%.o: %.cpp
	@mkdir -p ${dir $@}
	@${CC} ${CFLAGS} -o $@ -c $< -I includes
	@echo ${__GREEN}"Compiling "${__WHITE}$<${__EOC}

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@echo ${__GREEN}"Finished "${__WHITE}${NAME}" v"${VERSION}" bin target"${__EOC}

tests:
	@cd tester && ./do.sh

clean:
	@rm -rf bin/

fclean: clean
	@rm -rf ${NAME}
	@echo ${__BLUE}"Cleaned "${__WHITE}"bin target(s)"${__EOC}

re: fclean all

.PHONY: all fclean clean re

