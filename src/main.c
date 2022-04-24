/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 12:14:55 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/21 13:49:09 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    do_magic(t_data *data, int i)
{
    int len;
    char buf[301];

    if (data->id == 0)
    {
        ft_printf("I'm a child with id = %d. ", data->id);
        //ft_printf("fd[0]: %d, fd[1]: %d\n", data->fd_pipe[0], data->fd_pipe[1]);
        close(data->fd_pipe[0]);
        write(data->fd_pipe[1], data->argv[data->argc - i - 1], ft_strlen(data->argv[data->argc - i - 1]));
        close(data->fd_pipe[1]);
        ft_printf("executing command: %s\n", data->argv[data->argc - i - 1]);
    }
    else if (data->done == 0)
    {
        //waitpid(data->id, NULL, WUNTRACED);
        ft_printf("I'm a parent with id = %d. ", data->id);
        close(data->fd_pipe[1]);
        len = read(data->fd_pipe[0], buf, 300);
        if (len == -1)
        {
            ft_printf("Error: read failed\n");
            exit(EXIT_FAILURE);
        }
        buf[len] = '\0';
        ft_printf("I just read: [%s]\n", buf);
        close(data->fd_pipe[0]);
        data->done = 1;
    }
}

void    create_processes(int i, t_data *data)
{
    data->id = 0;
    while (i > 0)
    {
        if (data->id == 0)
        {
            if (pipe(data->fd_pipe) == -1)
			{
				ft_printf("Error: creating pipe failed\n");
				exit(EXIT_FAILURE);
			}
			data->id = fork();
            if (data->id == -1)
            {
                ft_printf("Error: fork failed\n");
                exit(EXIT_FAILURE);
            }
        }
        do_magic(data, i);
        i--;
    }
    
}

int	main(int argc, char **argv)//, char **env)
{
	t_data  data;
    int     i;

    i = 0;
	if (argc != 5)
		exit(EXIT_FAILURE);
	data = init_data(argc, argv);
    create_processes(2, &data);
	return (1);
}
