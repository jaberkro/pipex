/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   close_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 12:09:06 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/23 12:02:57 by jaberkro      ########   odam.nl         */
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

void	write_exit_argument(char *argument, char *message, int exit_code)
{
	if (argument)
		write(2, argument, ft_strlen(argument));
	write(2, message, ft_strlen(message));
	exit(exit_code);
}

void	free_nested_array(char **to_free)
{
	int	i;

	i = 0;
	while (to_free && to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

void	close3(int fd1, int fd2, int fd3)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	if (fd3 != -1)
		close(fd3);
}
