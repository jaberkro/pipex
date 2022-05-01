/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   files_programs_bonus.c.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 21:03:09 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/30 19:01:47 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	open_outputfile(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT, 0755);
	if (fd < 0)
		error_exit(file, 1);
	return (fd);
}

char	**get_paths(char **env)
{
	int		i;
	char	**paths;
	char	*tmp;

	i = 0;
	paths = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			paths = ft_split(env[i], ':');
			if (!paths)
				error_exit("malloc", 1);
			break ;
		}
		i++;
	}
	tmp = paths[0];
	paths[0] = ft_split(paths[0], '=')[1];
	if (paths[0] == NULL)
		error_exit("malloc", 1);
	free(tmp);
	return (paths);
}

static char	*make_path(char *path)
{
	char	*command;
	char	*tmp;

	command = ft_strdup(path);
	tmp = command;
	command = ft_strjoin(command, "/");
	free(tmp);
	if (command == NULL)
		error_exit("malloc", 1);
	return (command);
}

char	*command_in_paths(char *argument, char **paths)
{
	int		i;
	char	*command;
	char	*tmp;

	i = 0;
	if (access(argument, F_OK) != -1)
		return (argument);
	while (paths[i])
	{
		command = make_path(paths[i]);
		tmp = command;
		command = ft_strjoin(command, argument);
		free(tmp);
		if (command == NULL)
			error_exit("malloc", 1);
		if (access(command, F_OK) != -1)
			return (command);
		i++;
	}
	error_exit(argument, 1);
	return (NULL);
}

//65536 max
