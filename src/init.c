/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 14:10:18 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/20 11:38:40 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_outputfile(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		error_exit(file, 1);
	return (fd);
}

int	open_inputfile(char *file)
{
	int	fd;

	if (access(file, F_OK) == -1 || access(file, R_OK) == -1)
		error_exit(file, 1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit(file, 1);
	return (fd);
}

t_data	init_data(int argc, char **argv, char **env)
{
	t_data	data;

	data.heredoc = 0;
	data.argc = argc;
	data.argv = argv;
	data.env = env;
	data.paths = get_paths(data.env);
	return (data);
}
