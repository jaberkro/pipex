/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 14:00:43 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/14 22:23:02 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	check_input(int argc, char **argv)
{
	t_data data;

	data.fd1 = open(argv[1], O_RDONLY);
	if (data.fd1 < 0)
	{
		ft_printf("%s: %s\n", argv[1], strerror(2));
		exit(EXIT_FAILURE);
	}
	data.fd2 = open(argv[argc - 1], O_WRONLY);
	if (data.fd2 < 0)
	{
		execve("/bin/mkdir", &argv[argc - 1], NULL);
	}
		
	return (data);
}
