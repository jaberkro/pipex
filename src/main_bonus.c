/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 12:18:48 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/11 20:21:22 by jaberkro      ########   odam.nl         */
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

void	heredoc_execute(t_data data, int d2_out)
{
	char	*input;

	input = read_stdin_until(data.argv[2]);
	write(d2_out, input, ft_strlen(input));
	free(input);
}

pid_t	fork_execute(t_data data, char **commands, int d2_in, int d2_out)
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
	char	**command;
	pid_t	pid;

	command = ft_split(data.argv[i], ' ');
	if (command == NULL)
		error_exit("Malloc failed", 1);
	if (i == 2 && data.heredoc == 0)
		pid = fork_execute(data, command, data.fd_in, data.fd_pipes[i - 2][1]);
	else if (i == data.argc - 2)
	{
		data.fd_out = open_outputfile_bonus(data.argv[data.argc - 1], data.heredoc);
		pid = fork_execute(data, command, data.fd_pipes[i - 3][0],
				data.fd_out);
	}
	else
	{
		pid = fork_execute(data, command, data.fd_pipes[i - 3][0],
				data.fd_pipes[i - 2][1]);
	}
	free_nested_array(command);
	return (pid);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		i;
	pid_t	*pids;

	data = init_data(argc, argv, env);
	pids = malloc((argc - 3) * sizeof(pid_t));
	if (pids == NULL)
		error_exit("Malloc failed", 1);
	i = 2 + data.heredoc;
	if (data.heredoc == 1)
		heredoc_execute(data, data.fd_pipes[0][1]);
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
