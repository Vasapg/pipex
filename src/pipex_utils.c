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
#include "pipex.h"

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

void	execute_command(char **env, char *const command, char **flags)
{
	int		i;
	char	**paths;
	char	*path;

	paths = ft_split(get_path(env), ':');
	paths[0] = ft_substr(paths[0], 5, 100);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin (paths[i], "/");
		path = ft_strjoin (path, command);
		flags[0] = path;
		//printf("path final: %s\n", path);
		execve(path, flags, env);
		i++;
	}
	printf("ejecuto path directo: %s\n", command);
	execve(command, flags, env);
	close()
}
