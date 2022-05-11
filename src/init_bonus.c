/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/24 21:12:39 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/11 20:20:15 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_outputfile_bonus(char *file, int heredoc)
{
	int	fd;

	if (heredoc == 1)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT, 0644);
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

char	*read_stdin_until(char *limiter)
{
	char	*input;
	char	*buf;
	char	*tmp;

	input = ft_strdup("");
	if (input == NULL)
		error_exit("Malloc failed", 1);
	ft_printf(">");
	buf = get_next_line(0);
	if (buf == NULL)
		error_exit("Malloc failed", 1);
	while (!(ft_strncmp(buf, limiter, ft_strlen(limiter)) == 0 && \
			ft_strlen(buf) == ft_strlen(limiter) + 1))
	{
		tmp = input;
		input = ft_strjoin(input, buf);
		free(tmp);
		if (input == NULL)
			error_exit("Malloc failed", 1);
		ft_printf(">");
		free(buf);
		buf = get_next_line(0);
		if (buf == NULL)
			error_exit("Malloc failed", 1);
	}
	free(buf);
	return (input);
}

int	**create_pipes(int amount)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(((amount + 1) * sizeof(pipes)));
	if (pipes == NULL)
		error_exit("Malloc failed", 1);
	while (i < amount)
	{
		pipes[i] = malloc((2 * sizeof(int)));
		if (pipes[i] == NULL)
			error_exit("Malloc failed", 1);
		if (pipe(pipes[i]) < 0)
			error_exit("Pipe failed", 1);
		i++;
	}
	pipes[i] = NULL;
	return (pipes);
}

t_data	init_data(int argc, char **argv, char **env)
{
	t_data	data;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		data.heredoc = 1;
		data.fd_in = -1;
	}	
	else
	{
		data.heredoc = 0;
		data.fd_in = open_inputfile(argv[1]);
	}
	data.argc = argc;
	data.argv = argv;
	data.fd_pipes = create_pipes(argc - 4);
	data.env = env;
	data.paths = get_paths(data.env);
	return (data);
}
