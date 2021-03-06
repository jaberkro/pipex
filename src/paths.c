/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   paths.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 21:03:09 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/23 17:52:34 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*make_path(char *path)
{
	char	*command;
	char	*tmp;

	command = ft_strdup(path);
	if (command == NULL)
		error_exit("Malloc failed", 1);
	tmp = command;
	command = ft_strjoin(command, "/");
	free(tmp);
	if (command == NULL)
		error_exit("Malloc failed", 1);
	return (command);
}

char	*command_in_paths(char *argument, char **paths)
{
	int		i;
	char	*command;
	char	*tmp;

	i = 0;
	if (access(argument, X_OK) != -1)
		return (argument);
	if (!paths)
		write_exit_argument(argument, ": No such file or directory\n", 127);
	if (!argument)
		write_exit(": command not found\n", 127);
	while (paths && paths[i])
	{
		command = make_path(paths[i]);
		tmp = command;
		command = ft_strjoin(command, argument);
		free(tmp);
		if (command == NULL)
			error_exit("Malloc failed", 1);
		if (access(command, X_OK) != -1)
			return (command);
		i++;
	}
	write_exit_argument(argument, ": command not found\n", 127);
	return (NULL);
}

char	**get_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	paths = protected_split(env[i] + 5, ':');
	return (paths);
}
