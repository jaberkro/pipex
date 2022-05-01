/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 12:15:22 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/01 21:10:26 by jaberkro      ########   odam.nl         */
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
	int		fd_in;
	int		**fd_pipes;
	int		fd_out;
	int		argc;
	char	**argv;
	char	**env;
	char	**paths;
	int		heredoc;
}	t_data;

t_data	init_data(int argc, char **argv, char **env);

int		open_inputfile(char *file);
int		open_outputfile(char *file);
char	**get_paths(char **env);
char	*command_in_paths(char *argument, char **paths);

void	error_exit(char *message, int exit_code);
void	write_exit(char *message, int exit_code);
void	close_fds(t_data data);
void	free_nested_array(char **to_free);

char	*read_stdin_until(char *limiter);

#endif