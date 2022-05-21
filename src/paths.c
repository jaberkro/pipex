/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   paths.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 14:00:43 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/21 22:03:05 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	command_not_found(char *argument)
{
	if (argument)
		ft_printf("%s", argument);
	ft_printf(": command not found\n");
	exit(127);
}

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
	if (access(argument, F_OK) != -1)
		return(argument);
	if (!paths)
	{
		if (argument)
			ft_printf("%s", argument);
		ft_printf(": No such file or directory\n");
		exit(127); // maybe 127?
	}
	if (!argument)
		command_not_found(argument);
	while (paths && paths[i])
	{
		command = make_path(paths[i]);
		tmp = command;
		command = ft_strjoin(command, argument);
		free(tmp);
		if (command == NULL)
			error_exit("Malloc failed", 1);
		if (access(command, F_OK) != -1)
			return (command);
		i++;
	}
	ft_printf("%s: No such file or directory\n", argument);
	exit(127);
	return (NULL);
}

char	**get_paths(char **env)
{
	int		i;
	char	**paths;
	char	**first_paths;
	char	*tmp;

	i = 0;
	paths = NULL;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	paths = ft_split(env[i], ':');
	if (!paths)
		error_exit("Malloc failed", 1);
	tmp = paths[0];
	first_paths = ft_split(paths[0], '=');
	if (first_paths == NULL)
		error_exit("Malloc failed", 1);
	paths[0] = first_paths[1];
	free_nested_array(first_paths);
	free(tmp);
	return (paths);
}

void	check_permission_infile(int fd, char *argument)
{
	if (fd < 0)
	{
		if (fd == -1)
			ft_printf("%s: No such file or directory\n", argument);
		else if (fd == -2)
			ft_printf("%s: Permission denied\n", argument);
		exit(1);
	}	
}
