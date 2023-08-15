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

char	**flags_builder(char *argv)
{
	int		i;
	char	**flags;
	char	*free_me;

	i = 1;
	flags = ft_split(argv, ' ');
	free(flags[0]);
	while (flags[i])
	{
		free_me = flags[i];
		flags[i - 1] = flags[i];
		free(free_me);
		i++;
	}
	return (flags);
}

void	execute_command(char **env, char *const command, char *const *flags)
{
	int		i;
	char	**paths;
	char	*path;
	int		found;

	found = 0;
	i = 0;
	while (env[i] && found == 0)
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			found = 1;
		else
			i++;
	}
	printf("%s\n", env[i]);
	paths = ft_split(env[i], ':');
	paths[0] = ft_substr(paths[0], 5, 100);
	i = 0;
	while (paths[i])
	{
		printf("path numero %i :%s \n", i, paths[i]);
		path = ft_strjoin (paths[i], "/");
		path = ft_strjoin (path, command);
		printf("path final: %s \n", path);
		execve(path, flags, env);
		i++;
	}
	printf("Error Comando no encontrado");
}
