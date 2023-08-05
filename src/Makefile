# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsanz-ar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/28 13:51:49 by vsanz-ar          #+#    #+#              #
#    Updated: 2023/08/05 20:09:53 by vsanz-ar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#----------------------------------------LIBFT MAKE VARS------------------------------------------------

LIBPATH = ./libft
LIBA = ./libft/libft.a

#----------------------------------------PRINTFT MAKE VARS------------------------------------------------
NAME = pipex.a
FILES = pipex.c pipex_utils.c 
CFLAGS = -Wall -Wextra -Werror 
CC = gcc
RM = rm -f
FOBJ = ${FILES:.c=.o} 
#----------------------------------------PRINTFT MAKE RULES------------------------------------------------

all: ${NAME}

${NAME}: ${FOBJ}
	@make -C ${LIBPATH}
	@cp libft/libft.a .
	@mv libft.a ${NAME}
	ar -rcs ${NAME} ${FOBJ}
	${CC} pipex.c ${NAME} -o pipex

clean:
	@make clean -C ${LIBPATH}
	${RM} ${FOBJ} ${BOBJ} test.out

fclean: clean
	${RM} ${LIBA}
	${RM} ${NAME}

re: fclean all

#----------------------------------------LIBFT MAKE RULES-----------------------------------------------

.PHONY: all clean re fclean bonus libft 

