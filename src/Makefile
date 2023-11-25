# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsanz-ar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/28 13:51:49 by vsanz-ar          #+#    #+#              #
#    Updated: 2023/09/07 17:08:14 by vsanz.ar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#----------------------------------------LIBFT MAKE VARS------------------------------------------------

LIBPATH = ./libft
LIBA = ./libft/libft.a

#----------------------------------------PIPEX MAKE VARS------------------------------------------------
NAME = pipex.a
NAME_B = pipex_bonus.a
FILES = pipex.c pipex_utils.c 
BONUS = pipex_bonus.c pipex_utils_bonus.c 
CFLAGS = -Wall -Wextra -Werror -g
CC = gcc
RM = rm -f
FOBJ = ${FILES:.c=.o}
BOBJ = ${BONUS:.c=.o} 
#----------------------------------------PIPEX MAKE RULES------------------------------------------------

all: ${NAME}

${NAME}: ${FOBJ}
	@make -C ${LIBPATH}
	@cp libft/libft.a .
	@mv libft.a ${NAME}
	ar -rcs ${NAME} ${FOBJ}
	${CC} ${CFLAGS} pipex.c ${NAME} -o pipex

clean:
	@make clean -C ${LIBPATH}
	${RM} ${FOBJ} ${BOBJ} test.out

fclean: clean
	@make fclean -C ${LIBPATH}
	${RM} ${LIBA}
	${RM} ${NAME} ${NAME_B} pipex pipex_bonus

re: fclean all

#----------------------------------------PIPEX BONUS MAKE RULES-----------------------------------------------
bonus: ${NAME_B}

${NAME_B}: ${BOBJ}
	@make -C ${LIBPATH}
	@cp libft/libft.a .
	@mv libft.a ${NAME_B}
	ar -rcs ${NAME_B} ${BOBJ}
	${CC} ${CFLAGS} pipex_bonus.c ${NAME_B} -o pipex_bonus

.PHONY: all clean re fclean bonus libft 
