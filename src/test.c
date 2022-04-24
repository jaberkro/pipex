/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/24 21:12:39 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/24 22:38:08 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "pipex.h"

int main(int argc, char **argv, char **env)
{
    int input_fd = open_inputfile(argv[1]);
    int output_fd = open_outputfile(argv[argc - 1]);
    int fd[2];
    if (pipe(fd) == -1)
        exit(EXIT_FAILURE);
    
    int pid1 = fork();
    if (pid1 < 0)
        exit(EXIT_FAILURE);
    
    if (pid1 == 0)
    {
        char **commands;
        char **paths = get_paths(env);
        char *path;
        commands = ft_split(argv[2], ' ');
        path = command_in_paths(commands[0], paths);
        dup2(input_fd, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        if (execve(path, commands, env) < 0)
            exit(EXIT_FAILURE);
    }

    int pid2 = fork();
    if (pid2 < 0)
        exit(EXIT_FAILURE);

    if (pid2 == 0)
    {
        char **commands;
        char **paths = get_paths(env);
        char *path;
        commands = ft_split(argv[argc - 2], ' ');
        path = command_in_paths(commands[0], paths);
        dup2(output_fd, STDOUT_FILENO);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        if (execve(path, commands, env) < 0)
            exit(EXIT_FAILURE);
    }
    close(fd[0]);
    close(fd[1]);
    close(input_fd);
    close(output_fd);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return (1);
}