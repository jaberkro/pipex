/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 12:15:22 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/15 20:32:33 by jaberkro      ########   odam.nl         */
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
	int fd1;
	int fd2;
}   t_data;

t_data	init_data(int argc, char **argv);
t_data	get_input_output_fd(int argc, char **argv);

#endif