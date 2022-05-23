/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 12:18:48 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/23 15:19:44 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	heredoc_execute(t_data data, int heredoc_fd[2])
{
	char	*input;

	input = read_stdin_until(data.argv[2]);
	write(heredoc_fd[1], input, ft_strlen(input));
	close(heredoc_fd[1]);
	free(input);
}

static int	executer(int i, int max, int readfd, t_data data)
{
	int		fd[2];
	int		pid;
	char	*path;
	char	**command;

	protected_pipe(fd);
	pid = protected_fork();
	if (pid == 0)
	{
		if (i == 2 && data.heredoc == 0)
			readfd = open_inputfile(data.argv[1]);
		else if (i == max)
			fd[1] = open_outputfile(data.argv[data.argc - 1], data.heredoc);
		command = protected_split(data.argv[i], ' ');
		path = command_in_paths(command[0], data.paths);
		protected_dup2(fd[1], readfd);
		close3(readfd, fd[0], fd[1]);
		if (execve(path, command, data.env) < 0)
			error_exit("Execve failed", 1);
	}
	close3(readfd, fd[1], -1);
	if (i != max)
		pid = executer(i + 1, max, fd[0], data);
	return (pid);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		i;
	int		heredoc_fd[2];
	int		pid;
	int		status;

	if (argc < 5 || (argc < 6 && ft_strncmp(argv[1], "here_doc", 9) == 0))
		write_exit("Not enough arguments\n", 1);
	data = init_data(argc, argv, env);
	i = 2 + data.heredoc;
	heredoc_fd[0] = -1;
	if (data.heredoc == 1)
	{
		protected_pipe(heredoc_fd);
		heredoc_execute(data, heredoc_fd);
	}
	pid = executer(i, argc - 2, heredoc_fd[0], data);
	waitpid(pid, &status, 0);
	exit(WEXITSTATUS(status));
}
