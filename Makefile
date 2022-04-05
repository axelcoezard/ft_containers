# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 10:40:18 by acoezard          #+#    #+#              #
#    Updated: 2022/04/05 17:06:52 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

STD_NAME	:=	std_containers
FT_NAME		:=	ft_containers
VERSION		:=	1.0
ARCH		:=	x64

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
all: ${FT_NAME} ${STD_NAME}

${FT_NAME}:
	@${CC} ${CFLAGS} ${SRCS} -I includes -o ${FT_NAME}
	@echo ${__GREEN}"Finished "${__WHITE}${FT_NAME}" v"${VERSION}" bin target"${__EOC}

${STD_NAME}:
	@${CC} ${CFLAGS} ${SRCS} -I includes -DSTD=1 -o ${STD_NAME}
	@echo ${__GREEN}"Finished "${__WHITE}${STD_NAME}" v"${VERSION}" bin target"${__EOC}

test:
	@cd tests && ./do.sh

clean:
	@rm -rf bin/

fclean: clean
	@rm -rf ${FT_NAME} ${STD_NAME}
	@echo ${__BLUE}"Cleaned "${__WHITE}"bin target(s)"${__EOC}

re: fclean all

.PHONY: all fclean clean re

