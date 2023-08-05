/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-ar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:56:01 by vsanz-ar          #+#    #+#             */
/*   Updated: 2023/08/05 21:07:34 by vsanz-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

void dad(char *argv[], int fd[2], int child)
{
	char buff[2048];

	//waitpid(child, NULL, NULL);
	read(fd[0], buff, 2048);
	printf("%s", buff);
}

void child(char *argv[], int fd[2])
{
	fd = open(argv[1], O_RDONLY);
	dup2(fd[1], 0);
	execvp(argv[2], "");
}

int	main(int argc, char *argv[])
{
	int	err;
	int	fd[2];

/*	if (argc != 5)
	{
		perror("Error, uso: archivo 1 comando 1 comando 2 archivo 2");
		return (-1);
	}*/
	err = pipe(fd);
	if (err == -1)
	{
		perror("Error al crear la pipe");
		return (-1);
	}
	err = fork();
	if (err != 0 && err != -1)
		dad(argv, fd, err);
	else if (err == 0)
		child(argv, fd);
}
