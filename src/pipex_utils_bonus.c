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
	{
			perror("El comando no pudo ser ejecutado");
	}
	exit(1);
}
