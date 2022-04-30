/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 14:10:18 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/30 22:37:09 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	init_data(int argc, char **argv, char **env)
{
	t_data	data;

	data.fd_in = open_inputfile(argv[1]);
	data.argc = argc;
	data.argv = argv;
	if (pipe(data.fd_pipe) < 0)
		error_exit("Pipe failed", 1);
	data.env = env;
	data.paths = get_paths(data.env);
	return (data);
}
