/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 12:14:55 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/30 22:42:08 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_for_pids(pid_t *pids)
{
	int	i;

	i = 0;
	while (pids && pids[i])
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
}

pid_t	fork_and_execute(t_data data, char **commands, int d2_in, int d2_out)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid < 0)
		error_exit("Fork failed", 1);
	if (pid == 0)
	{
		path = command_in_paths(commands[0], data.paths);
		if (path == NULL)
			error_exit(commands[0], 127);
		if (dup2(d2_in, STDIN_FILENO) < 0)
			error_exit("Dup2 failed", 1);
		if (dup2(d2_out, STDOUT_FILENO) < 0)
			error_exit("Dup2 failed", 1);
		close(d2_in);
		close(d2_out);
		close_fds(data);
		if (execve(path, commands, data.env) < 0)
			error_exit("Execve failed", 1);
	}
	return (pid);
}

pid_t	execute_command(t_data data, int i)
{
	char	**commands;
	pid_t	pid;

	commands = ft_split(data.argv[i], ' ');
	if (commands == NULL)
		error_exit("Malloc failed", 1);
	if (i == 2)
		pid = fork_and_execute(data, commands, data.fd_in, data.fd_pipe[1]);
	else
	{
		data.fd_out = open_outputfile(data.argv[data.argc - 1]);
		pid = fork_and_execute(data, commands, data.fd_pipe[0], data.fd_out);
	}
	free_nested_array(commands);
	return (pid);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		i;
	pid_t	*pids;

	if (argc < 5 || argc > 5)
		write_exit("Amount of arguments must be 4\n", 1);
	data = init_data(argc, argv, env);
	pids = malloc((argc - 3) * sizeof(pid_t));
	if (pids == NULL)
		error_exit("Malloc failed", 1);
	i = 2;
	while (i < argc - 1)
	{
		pids[i - 2] = execute_command(data, i);
		i++;
	}
	pids[i] = 0;
	close_fds(data);
	wait_for_pids(pids);
	return (1);
}
