# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsanz-ar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/28 13:51:49 by vsanz-ar          #+#    #+#              #
#    Updated: 2023/09/06 18:43:47 by vsanz-ar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#----------------------------------------LIBFT MAKE VARS------------------------------------------------

LIBPATH = ./libft
LIBA = ./libft/libft.a

#----------------------------------------PIPEX MAKE VARS------------------------------------------------
NAME = pipex.a
FILES = pipex.c pipex_utils.c 
CFLAGS = -Wall -Wextra -Werror 
CC = gcc
RM = rm -f
FOBJ = ${FILES:.c=.o} 
#----------------------------------------PIPEX MAKE RULES------------------------------------------------

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
	@make fclean -C ${LIBPATH}
	${RM} ${LIBA}
	${RM} ${NAME} 

re: fclean all

#----------------------------------------LIBFT MAKE RULES-----------------------------------------------

.PHONY: all clean re fclean bonus libft 

