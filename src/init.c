/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 14:10:18 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/15 20:32:25 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	init_data(int argc, char **argv)
{
	t_data	data;

	data = get_input_output_fd(argc, argv);
	return (data);
}
