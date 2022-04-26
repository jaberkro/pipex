/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 12:15:22 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/26 15:33:07 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX
# define PIPEX
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_data{
	int 	fd_in;
	int		fd_pipe[2];
	int 	fd_out;
	int		argc;
	char	**argv;
	char	**env;
	char	**paths;
}   t_data;

t_data  init_data(int argc, char **argv, char **env);
t_data	get_input_output_fd(int argc, char **argv);

char	**get_paths(char **env);
char	*command_in_paths(char *argument, char **paths);

int	open_outputfile(char *file);
int	open_inputfile(char *file);

void    error_exit(char *message, int exit_code);


#endif