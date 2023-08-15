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

void	child(char *const command, char *const *flags, char **env)
{
	execute_command(env, command, flags);
}

void	ft_pipex(int counter, int fd[2], char *argv[], char **env)
{
	int		input;
	int		output;
	int		pid;
	char	**flags;

	if (counter == 0)
		input = open(argv[1], O_RDONLY | O_CREAT, 0777);
	else
		input = fd[0];
	if (counter == 1)
		output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		output = fd[1];
	pid = fork();
	if (pid == 0)
	{
		printf("command:%s", argv[counter + 2]);
		close(0);
		dup(input);
		close(1);
		dup(output);
		flags = flags_builder(argv[counter + 2]);
		child(argv[counter + 2], flags, env);
	}
}

int	main(int argc, char *argv[], char **env)
{
	int	err;
	int	fd[2];
	int	i;

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
		ft_pipex(i, fd, argv, env);
		i++;
	}
}
