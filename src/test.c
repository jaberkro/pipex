/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/24 21:12:39 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/26 15:48:53 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
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

void	fork_and_execute_first(t_data data, char **commands)
{
	int		pid;
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
		close(data.fd_pipe[0]);
		close(data.fd_pipe[1]);
		if (execve(path, commands, data.env) < 0)
			error_exit("execve", 1);
		close(data.fd_pipe[0]);
		close(data.fd_pipe[1]);
		close(data.fd_in);
		close(data.fd_out);
		waitpid(pid, NULL, 0);
	}
}

void	fork_and_execute_middle(t_data data, char **commands)
{
	int		pid;
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
		if (dup2(data.fd_pipe[1], STDOUT_FILENO) < 0)
			error_exit("dup2", 1);
		close(data.fd_pipe[0]);
		close(data.fd_pipe[1]);
		if (execve(path, commands, data.env) < 0)
			error_exit("execve", 1);
		close(data.fd_pipe[0]);
		close(data.fd_pipe[1]);
		close(data.fd_in);
		close(data.fd_out);
		waitpid(pid, NULL, 0);
	}
}

void	fork_and_execute_last(t_data data, char **commands)
{
	int		pid;
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
		close(data.fd_pipe[0]);
		close(data.fd_pipe[1]);
		if (execve(path, commands, data.env) < 0)
			error_exit("execve", 1);
		close(data.fd_in);
		close(data.fd_out);
		close(data.fd_pipe[0]);
		close(data.fd_pipe[1]);
		waitpid(pid, NULL, 0);
	}
}

t_data	init_data(int argc, char **argv, char **env)
{
	t_data	data;

	data.fd_in = open_inputfile(argv[1]);
	data.fd_out = open_outputfile(argv[argc - 1]);
	data.argc = argc;
	data.argv = argv;
	if (pipe(data.fd_pipe) < 0)
		error_exit("pipe", 1);
	data.env = env;
	data.paths = get_paths(data.env);
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	**commands;
	int		i;

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
			fork_and_execute_first(data, commands);
		else if (i == argc - 2)
			fork_and_execute_last(data, commands);
		else
			fork_and_execute_middle(data, commands);
		i++;
	}
	return (1);
}

/*
	things to fix:
	- norminette proof
	- bonus part
	- waitpid at correct place?

	perror als er een errno is gemaakt
	
*/