/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 12:14:55 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/21 20:47:17 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	protected_dup2(int writefd, int readfd)
{
	if (dup2(writefd, STDOUT_FILENO) < 0)
		error_exit("Dup2 failed", 1);
	if (dup2(readfd, STDIN_FILENO) < 0)
		error_exit("Dup2 failed", 1);
}

static int	protected_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error_exit("Fork failed", 1);
	return (pid);
}

static void	executer(int i, int max, int readfd, t_data data)
{
	int		fd[2];
	int		pid;
	char	*path;
	char	**command;

	if (pipe(fd) < 0)
		error_exit("Pipe failed", 1);
	pid = protected_fork();
	if (pid == 0)
	{
		check_permission_infile(readfd, data.argv[i - 1]);
		if (i == max)
			fd[1] = open_outputfile(data.argv[data.argc - 1], data.heredoc);
		command = ft_split(data.argv[i], ' ');
		if (command == NULL)
			error_exit("Malloc failed", 1);
		path = command_in_paths(command[0], data.paths);
		protected_dup2(fd[1], readfd);
		close3(readfd, fd[0], fd[1]);
		if (execve(path, command, data.env) < 0)
			command_not_found(command[0]);
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
	int		status;

	if (argc < 5 || argc > 5)
		write_exit("Amount of arguments must be 4\n", 1);
	data = init_data(argc, argv, env);
	fdin = open_inputfile(data.argv[1]);
	i = 2;
	executer(i, argc - 2, fdin, data);
	while (	waitpid(-1, &status, 0) != -1)
	{
		i++;
	}
	exit(WEXITSTATUS(status));
}
