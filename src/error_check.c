/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 14:00:43 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/26 15:13:59 by jaberkro      ########   odam.nl         */
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

// t_data	get_input_output_fd(int argc, char **argv)
// {
// 	t_data	data;

// 	data.fd_in = open_inputfile(argv[1]);
// 	data.fd_out = open_outputfile(argv[argc - 1]);
// 	return (data);
// }

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
		command = ft_strdup(paths[i]);
		tmp = command;
		command = ft_strjoin(command, "/");
		free(tmp);
		if (command == NULL)
			error_exit("malloc", 1);
		tmp = command;
		command = ft_strjoin(command, argument);
		free(tmp);
		if (command == NULL)
			error_exit("malloc", 1);
		if (access(command, F_OK) != -1)
			return (command);
		i++;
	}
	perror(argument);
	exit(EXIT_FAILURE);
}

// void	check_commands(int argc, char **argv, char **env)
// {
// 	int		i;
// 	char	**paths;

// 	i = 2;
// 	paths = get_paths(env);
// 	while (i < argc - 1)
// 	{
// 		if (!command_in_paths(argv[i], paths))
// 			ft_printf("INVALID COMMAND: %s\n", argv[i]);
// 		i++;
// 	}
// }




//65536 max