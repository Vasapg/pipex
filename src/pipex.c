/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-ar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:56:01 by vsanz-ar          #+#    #+#             */
/*   Updated: 2023/08/05 20:57:04 by vsanz-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>

int	main(int argc, char *argv[])
{
	int	err;
	int	fd[2];

	if (argc != 5)
	{
		perror("Error, uso: archivo 1 comando 1 comando 2 archivo 2");
		return (-1);
	}
	err = pipex(fd);
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

void dad(char *argv[], int fd[2], int child)
{
	waitpid(child);
	read()
}

void child(char *argv[], int fd[2])
{
	int	fd;

	fd = open(argv[1], O_RDONLY, 0777);
	dup2(fd[], 0);
	execvp(argv[2], "");
}
