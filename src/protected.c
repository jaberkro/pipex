/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   protected_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 11:18:52 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/23 12:10:43 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	protected_dup2(int writefd, int readfd)
{
	if (dup2(writefd, STDOUT_FILENO) < 0)
		error_exit("Dup2 failed", 1);
	if (dup2(readfd, STDIN_FILENO) < 0)
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

char	**protected_split(char *to_split, char delimiter)
{
	char	**output;

	output = ft_split(to_split, delimiter);
	if (output == NULL)
		error_exit("Malloc failed", 1);
	return (output);
}

void	protected_pipe(int fd[2])
{
	if (pipe(fd) < 0)
		error_exit("Pipe failed", 1);
}
