/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 12:14:55 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/30 20:29:48 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *message, int exit_code)
{
	perror(message);
	exit(exit_code);
}

void	write_exit(char *message, int exit_code)
{
	write(2, message, ft_strlen(message));
	exit(exit_code);
}

void	close_fds(t_data data)
{
	close(data.fd_pipe[0]);
	close(data.fd_pipe[1]);
	close(data.fd_in);
	close(data.fd_out);
}

pid_t	fork_and_execute_first(t_data data, char **commands)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		path = command_in_paths(commands[0], data.paths);
		if (path == NULL)
			error_exit(commands[0], 127);
		if (dup2(data.fd_in, STDIN_FILENO) < 0)
			error_exit("dup2", 1);
		if (dup2(data.fd_pipe[1], STDOUT_FILENO) < 0)
			error_exit("dup2", 1);
		close_fds(data);
		if (execve(path, commands, data.env) < 0)
			error_exit("execve", 1);
	}
	return (pid);
}

pid_t	fork_and_execute_last(t_data data, char **commands)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		path = command_in_paths(commands[0], data.paths);
		if (path == NULL)
			error_exit(commands[0], 127);
		if (dup2(data.fd_pipe[0], STDIN_FILENO) < 0)
			error_exit("dup2", 1);
		if (dup2(data.fd_out, STDOUT_FILENO) < 0)
			error_exit("dup2", 1);
		close_fds(data);
		if (execve(path, commands, data.env) < 0)
			error_exit("execve", 1);
	}
	return (pid);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	**commands;
	int		i;
	pid_t	pids[2];

	if (argc < 5)
		write_exit("Error: Too little arguments\n", 1);
	else if (argc > 5)
		write_exit("Error: Too much arguments\n", 1);
	data = init_data(argc, argv, env);
	i = 2;
	while (i < argc - 1)
	{
		commands = ft_split(data.argv[i], ' ');
		if (commands == NULL)
			error_exit("malloc", 1);
		if (i == 2)
			pids[0] = fork_and_execute_first(data, commands);
		else
			pids[1] = fork_and_execute_last(data, commands);
		i++;
	}
	close_fds(data);
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);
	return (1);
}
