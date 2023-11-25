/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-ar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:06:22 by vsanz-ar          #+#    #+#             */
/*   Updated: 2023/08/05 20:06:58 by vsanz-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex_bonus.h"

char	**flags_builder(char *command)
{
	char	**flags;

	flags = ft_split(command, ' ');
	return (flags);
}

char	*get_path(char **env)
{
	int		i;
	int		found;

	found = 0;
	i = 0;
	while (env[i] && found == 0)
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

void	manage_fd(int input, int output, int fd[2])
{
	dup2(input, STDIN_FILENO);
	close(input);
	dup2(output, STDOUT_FILENO);
	close(output);
	close(fd[IN]);
	close(fd[OUT]);
}

void	free_str(char **flags, char **paths)
{
	int	i;

	i = 0;
	while (flags[i])
	{
		free(flags[i]);
		i++;
	}
	i = 0;
	free(flags);
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	execute_command(char **env, char *const command, char **flags)
{
	int		i;
	char	**paths;
	char	*path;

	paths = ft_split(get_path(env), ':');
	if (paths != NULL)
	{
		paths[0] = ft_substr(paths[0], 5, 100);
		i = 0;
		if (ft_strncmp("./", command, 2) != 0)
		{
			while (paths[i])
			{
				path = ft_strjoin (paths[i], "/");
				path = ft_strjoin (path, command);
				flags[0] = path;
				execve(path, flags, env);
				i++;
			}
		}
	}
	if (execve(command, flags, env) == -1)
		ft_putstr_fd("pipex: command not found\n", 2);
	free_str(flags, paths);
	exit(1);
}
