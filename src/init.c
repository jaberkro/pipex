/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 14:10:18 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/21 16:22:18 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_outputfile(char *file, int heredoc)
{
	int	fd;

	if (heredoc == 1)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		error_exit(file, 1);
	return (fd);
}

int	open_inputfile(char *file)
{
	int	fd;

	if (access(file, F_OK) == -1)
		return (-1);
	if (access(file, R_OK) == -1)
		return (-2);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Open failed", 1);
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
