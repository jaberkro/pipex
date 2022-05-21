/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 12:15:22 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/21 19:14:24 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_data{
	int		argc;
	char	**argv;
	char	**env;
	char	**paths;
	int		heredoc;
}	t_data;

int		open_inputfile(char *file);
int		open_outputfile(char *file, int heredoc);
char	*read_stdin_until(char *limiter);
t_data	init_data(int argc, char **argv, char **env);

void	command_not_found(char *argument);
char	*command_in_paths(char *argument, char **paths);
char	**get_paths(char **env);
void	check_permission_infile(int fd, char *argument);

void	error_exit(char *message, int exit_code);
void	write_exit(char *message, int exit_code);
void	free_nested_array(char **to_free);
void	close3(int fd1, int fd2, int fd3);

#endif