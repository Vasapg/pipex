/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-ar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:56:01 by vsanz-ar          #+#    #+#             */
/*   Updated: 2023/08/10 19:12:07 by vsanz-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void check_acces(char *argv[], int counter, int fd[2])
{
	int		input;
	int		output;
	
	input = IN;
	output = OUT;
	if(counter == 0 && access(argv[1], R_OK) != -1)
		input = open(argv[1], O_RDONLY, 0777);
	else if (counter == 0)
		perror("No existe permiso de lectura para el fichero de entrada");
	else
		input = fd[IN];
	if (counter == 1 && access(argv[4], W_OK) != -1)
		output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (counter == 1)
		perror("No existe permiso de lectura para el fichero de salida");
	else
		output = fd[OUT];
	close(IN);
	dup(input);
	close(OUT);
	dup(output);
	close(fd[IN]);
	close(fd[OUT]);
}

int	ft_pipex(int counter, int fd[2], char *argv[], char **env)
{
	int		pid;
	char	**flags;

	pid = fork();
	if (pid == 0)
	{
		check_acces(argv, counter, fd);
		flags = flags_builder(argv[counter + 2]);
		execute_command(env, flags[0], flags);
	}
	return (pid);
}

int	main(int argc, char *argv[], char **env)
{
	int	err;
	int	fd[2];
	int	i;
	int	pid;

	i = 0;
	if (argc != 5)
	{
		perror("Error, uso: archivo 1 comando 1 comando 2 archivo 2");
		return (-1);
	}
	err = pipe(fd);
	if (err == -1)
	{
		perror("Error al crear la pipe");
		return (-1);
	}
	while (i < 2)
	{
		pid = ft_pipex(i, fd, argv, env);
		i++;
	}
	close(fd[IN]);
	close(fd[OUT]);
	waitpid(pid, 0, 0);
}
