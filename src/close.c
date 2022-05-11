/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 21:15:46 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/01 13:59:56 by jaberkro      ########   odam.nl         */
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
	int	i;

	i = 0;
	while (data.fd_pipes && data.fd_pipes[i] != NULL)
	{
		close(data.fd_pipes[i][0]);
		close(data.fd_pipes[i][1]);
		i++;
	}
	close(data.fd_in);
	close(data.fd_out);
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
