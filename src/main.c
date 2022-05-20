/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 12:14:55 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/20 11:38:27 by jaberkro      ########   odam.nl         */
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

void	protected_dup2(int newfd, int oldfd)
{
	if (dup2(newfd, oldfd) < 0)
		error_exit("Dup2 failed", 1);
}

int	protected_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error_exit("Fork failed", 1);
	return (pid);
}

void	executer(int i, int max, int readfd, t_data data)
{
	int		fd[2];
	int		pid;
	char	*path;
	char	**command;

	command = ft_split(data.argv[i], ' ');
	if (command == NULL)
		error_exit("Malloc failed", 1);
	path = command_in_paths(command[0], data.paths);
	if (pipe(fd) < 0)
		error_exit("Pipe failed", 1);
	pid = protected_fork();
	if (pid == 0)
	{
		if (i == max)
			fd[1] = open_outputfile(data.argv[data.argc - 1]);
		protected_dup2(fd[1], STDOUT_FILENO);
		protected_dup2(readfd, STDIN_FILENO);
		close3(readfd, fd[0], fd[1]);
		if (execve(path, command, data.env) < 0)
			error_exit("Execve failed", 1);
	}
	close3(readfd, fd[1], -1);
	if (i != max)
		executer(i + 1, max, fd[0], data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		i;
	int		fdin;

	if (argc < 5 || argc > 5)
		write_exit("Amount of arguments must be 4\n", 1);
	data = init_data(argc, argv, env);
	fdin = open_inputfile(data.argv[1]);
	i = 2;
	executer(i, argc - 2, fdin, data);
	while (i < argc - 2)
	{
		waitpid(-1, NULL, WUNTRACED);
		i++;
	}
	return (1);
}
