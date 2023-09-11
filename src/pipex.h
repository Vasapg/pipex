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

int		ft_pipex(int fd[2], char *argv[], char **env);
int		main(int argc, char *argv[], char **env);
char	**flags_builder(char *command);
char	*get_path(char **env);
void	execute_command(char **env, char *const command, char **flags);
int		check_access(char *argv[], int counter, int fd[2]);
void	manage_fd(int input, int output, int fd[2]);
#endif
