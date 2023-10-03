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

void	init_inf(pipe_info *info, const char *in, const char *out, int argc)
{
	info->max = argc - 3;
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

int	ft_pipex(char *argv[], char **env, pipe_info info)
{
	int counter;
	int fd[2];
	int	pid;
	char **flags;

	counter = 0;
	while (counter < info.max)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			flags = flags_builder(argv[counter + 2]);
			if (counter == 0)
				manage_fd(info.in, fd[OUT], fd);
			else if (counter == (info.max - 1))
				manage_fd(info.saved, info.out, fd);
			else 
				manage_fd(info.saved, fd[OUT], fd);
			if (!(info.in == -1 && counter == 0) && !(info.out == -1 && counter == (info.max - 1)))
				execute_command(env, flags[0], flags);
			else
				exit(1);
		}
		info.saved = fd[IN];
		close(fd[OUT]);
		counter++;
	}
	return 1;
}

void	fre(void)
{
	system("leaks -q pipex");
}

int	main(int argc, char *argv[], char **env)
{
	int	err;
	int	status;
	pipe_info *pipe_inf; 

	status = 0;
	if (argc < 5)
	{
		perror("Error, uso: archivo 1 comando 1 ... comando X archivo 2");
		return (-1);
	}
	pipe_inf = malloc(sizeof(struct pipe_info));
	init_inf(pipe_inf, argv[1], argv[argc - 1], argc);
	ft_pipex(argv, env, *pipe_inf);
	free(pipe_inf);
	while ((wait(&err)) > 0)
		wait(&err);
	if (WIFEXITED(status))
	{
		//fre();
		exit(WEXITSTATUS(status));
	}
	fre();
	exit(1);
}
