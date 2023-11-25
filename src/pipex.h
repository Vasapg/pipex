/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-ar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:56:15 by vsanz-ar          #+#    #+#             */
/*   Updated: 2023/08/05 20:01:09 by vsanz-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft/libft.h"
# define IN 0
# define OUT 1

typedef struct pipe_info
{
	int		in;
	int		out;
	int		saved;
	int		max;
	char	**env;
}	t_pipe_info;

int		ft_pipex(char *argv[], t_pipe_info info);
int		main(int argc, char *argv[], char **env);
char	**flags_builder(char *command);
char	*get_path(char **env);
void	execute_command(char **env, char *const command, char **flags);
void	init_inf(t_pipe_info *info, const char *in,
			const char *out, char **env);
void	manage_fd(int input, int output, int fd[2]);
void	free_str(char **flags, char **paths);
void	handle_error(char **flags, char **paths, char *command);
void	error_msg(const char *file, const char *error);
#endif
