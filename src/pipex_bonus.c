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

void	init_inf(t_pipe_info *info, const char *in, const char *out, char **env)
{
	info->env = env;
	if (access(in, R_OK) != -1)
		info->in = open(in, O_RDONLY, 0777);
	else
	{
		info->in = -1;
		perror("Not enough permissions to read the input file");
	}
	if (access(out, W_OK) != -1)
		info->out = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (access(out, F_OK) == -1)
		info->out = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
	{
		info->out = -1;
		perror("The exit file does not exist or permissions are not enough");
	}
}

void	execute_child(t_pipe_info info, char *argv [], int counter, int fd[2])
{
	char	**flags;

	flags = flags_builder(argv[counter + 2]);
	if (counter == 0)
		manage_fd(info.in, fd[OUT], fd);
	else if (counter == (info.max - 1))
		manage_fd(info.saved, info.out, fd);
	else
		manage_fd(info.saved, fd[OUT], fd);
	if (!(info.in == -1 && counter == 0)
		&& !(info.out == -1 && counter == (info.max - 1)))
		execute_command(info.env, flags[0], flags);
	else
		exit(1);
}

void	ft_pipex(char *argv[], t_pipe_info info)
{
	int		counter;
	int		fd[2];
	int		pid;

	counter = 0;
	while (counter < info.max)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
			execute_child(info, argv, counter, fd);
		info.saved = fd[IN];
		close(fd[OUT]);
		counter++;
	}
}

void	fre(void)
{
	system("leaks -q pipex");
}

int	main(int argc, char *argv[], char **env)
{
	int			err;
	int			status;
	t_pipe_info	*info;

	status = 0;
	if (argc < 5)
	{
		perror("Error, uso: archivo 1 comando 1 ... comando X archivo 2");
		return (-1);
	}
	info = malloc(sizeof(t_pipe_info));
	init_inf(info, argv[1], argv[argc - 1], env);
	info->max = (argc - 3);
	ft_pipex(argv, *info);
	free(info);
	while ((wait(&err)) > 0)
		wait(&err);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	fre();
	exit(1);
}
