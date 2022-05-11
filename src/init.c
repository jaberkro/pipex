/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 14:10:18 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/11 18:42:21 by jaberkro      ########   odam.nl         */
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

int	**create_pipes(int amount)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(((amount + 1) * sizeof(pipes)));
	if (pipes == NULL)
		error_exit("Malloc failed", 1);
	while (i < amount)
	{
		pipes[i] = malloc((2 * sizeof(int)));
		if (pipes[i] == NULL)
			error_exit("Malloc failed", 1);
		if (pipe(pipes[i]) < 0)
			error_exit("Pipe failed", 1);
		i++;
	}
	pipes[i] = NULL;
	return (pipes);
}

t_data	init_data(int argc, char **argv, char **env)
{
	t_data	data;

	data.fd_in = open_inputfile(argv[1]);
	data.heredoc = 0;
	data.argc = argc;
	data.argv = argv;
	data.fd_pipes = create_pipes(argc - 4);
	data.env = env;
	data.paths = get_paths(data.env);
	return (data);
}
