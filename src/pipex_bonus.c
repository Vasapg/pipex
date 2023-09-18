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
#include "pipex_bonus.h"

void	manage_fd(int input, int output, int fd[2])
{
	close(IN);
	dup(input);
	close(OUT);
	dup(output);
	close(fd[IN]);
	close(fd[OUT]);
	close(input);
	close(output);
}

int	check_access(char *argv[], int argc, int fd[2], int counter)
{
	int		input;
	int		output;

	input = IN;
	output = OUT;
	if (counter == 0 && access(argv[1], R_OK) != -1)
		input = open(argv[1], O_RDONLY, 0777);
	else if (counter == 0)
		input = -1;
	else
		input = fd[IN];
	if (counter != 0 && access(argv[4], W_OK) != -1)
		output = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (counter != 0 && access(argv[4], F_OK) == -1)
		output = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (counter != 0)
		input = -1;
	else
		output = fd[OUT];
	if (input == -1)
		perror("No se tienen permisos suficientes sobre los ficheros dados");
	manage_fd(input, output, fd);
	return (input);
}

int	ft_pipex(char *argv[], char **env, int argc)
{
	int		pid;
	char	**flags;
	int		counter;
	int		fd[2];
	int		input;

	counter = 0;
	while (counter < argc - 3)
	{
		if (pipe(fd) == -1)
		{
			perror("Error al crear la pipe");
			return (-1);
		}
		pid = fork();
		if (pid == 0)
		{
			if (counter == 0 || counter == argc - 4)
			{
				if (check_access(argv, argc, fd, counter) == -1)
					exit(1);
			}
			else
				manage_fd(input, fd[1], fd);
			flags = flags_builder(argv[counter + 2]);
			execute_command(env, flags[0], flags);
		}
		close(input);
		close(fd[OUT]);
		input = fd[IN];
		counter++;
	}
	return (pid);
}

int	main(int argc, char *argv[], char **env)
{
	int	err;
	int	status;

	status = 0;
	if (argc < 5)
	{
		perror("Error, uso: archivo 1 comando 1 ... comando X archivo 2");
		return (-1);
	}
	err = ft_pipex(argv, env, argc);
	while ((wait(&err)) > 0)
		wait(&err);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	exit(-1);
}
