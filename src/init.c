/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/24 21:12:39 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/23 15:20:13 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_outputfile(char *file, int heredoc)
{
	int	fd;

	if (heredoc == 1)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		error_exit(file, 1);
	return (fd);
}

int	open_inputfile(char *file)
{
	int	fd;

	if (access(file, F_OK) == -1 || access(file, R_OK) == -1)
		error_exit(file, 1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit(file, 1);
	return (fd);
}

static void	request_next_line(char **buf)
{
	ft_printf(">");
	*buf = get_next_line(0);
	if (*buf == NULL)
		error_exit("Malloc failed", 1);
}

char	*read_stdin_until(char *limiter)
{
	char	*input;
	char	*buf;
	char	*tmp;

	input = ft_strdup("");
	if (input == NULL)
		error_exit("Malloc failed", 1);
	request_next_line(&buf);
	while (!(ft_strncmp(buf, limiter, ft_strlen(limiter)) == 0 && \
			ft_strlen(buf) == ft_strlen(limiter) + 1))
	{
		tmp = input;
		input = ft_strjoin(input, buf);
		free(tmp);
		if (input == NULL)
			error_exit("Malloc failed", 1);
		free(buf);
		request_next_line(&buf);
	}
	free(buf);
	return (input);
}

t_data	init_data(int argc, char **argv, char **env)
{
	t_data	data;

	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		data.heredoc = 1;
	else
		data.heredoc = 0;
	data.argc = argc;
	data.argv = argv;
	data.env = env;
	data.paths = get_paths(data.env);
	return (data);
}
