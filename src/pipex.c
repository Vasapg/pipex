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

void	manage_fd(int input, int output, int fd[2])
{
	close(IN);
	dup(input);
	close(OUT);
	dup(output);
	close(fd[IN]);
	close(fd[OUT]);
}

int	check_acces(char *argv[], int counter, int fd[2])
{
	int		input;
	int		output;

	input = IN;
	output = OUT;
	if (counter == 0 && access(argv[1], R_OK) != -1)
		input = open(argv[1], O_RDONLY, 0777);
	else if (counter == 0)
	{
		perror("No existe permiso de lectura para el fichero de entrada");
		input = -1;
	}
	else
		input = fd[IN];
	if (counter == 1 && access(argv[4], W_OK) != -1)
		output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (counter == 1)
	{
		perror("No existe permiso de lectura para el fichero de salida");
		input = -1;
	}
	else
		output = fd[OUT];
	manage_fd(input, output, fd);
	return (input);
}

int	ft_pipex(int fd[2], char *argv[], char **env)
{
	int		pid;
	char	**flags;
	int		counter;

	counter = 0;
	while (counter < 2)
	{
		pid = fork();
		if (pid == 0)
		{
			if (check_acces(argv, counter, fd) == -1)
				exit(1);
			flags = flags_builder(argv[counter + 2]);
			execute_command(env, flags[0], flags);
		}
		counter++;
	}
	close(fd[IN]);
	close(fd[OUT]);
	return (pid);
}

int	main(int argc, char *argv[], char **env)
{
	int	err;
	int	fd[2];
	int	status;

	status = 0;
	if (argc != 5)
	{
		perror("Error, uso: archivo 1 comando 1 comando 2 archivo 2");
		return (-1);
	}
	if (pipe(fd) == -1)
	{
		perror("Error al crear la pipe");
		return (-1);
	}
	err = ft_pipex(fd, argv, env);
	waitpid(err, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	exit(-1);
}
