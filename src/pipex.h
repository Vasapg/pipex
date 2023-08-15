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

#include <stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include "libft/libft.h"

void	child(char *const command, char *const *flags, char **env);
void    ft_pipex(int counter, int fd[2], char *argv[], char **env);
int	    main(int argc, char *argv[], char **env);
char	**flags_builder(char *argv);
void	execute_command(char **env, char *const command, char *const *flags);
