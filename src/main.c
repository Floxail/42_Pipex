/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 08:58:55 by flvejux           #+#    #+#             */
/*   Updated: 2026/01/05 08:58:55 by flvejux          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** init_data - Initializes the pipex data structure
*/
static void	init_data(t_pipex *data)
{
	data->infile = -1;
	data->outfile = -1;
	data->cmd1 = NULL;
	data->cmd2 = NULL;
	data->envp = NULL;
	data->paths = NULL;
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
}

/*
** main - Entry point for pipex program
** Flow:
** 1. Parse and validate arguments
** 2. Extract PATH from environment
** 3. Execute pipeline (fork, pipe, exec)
** 4. Cleanup and exit
*/

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	init_data(&data);
	data.envp = envp;
	if (parse_arguments(argc, argv, &data) == -1)
		return (EXIT_FAILURE);
	data.paths = get_paths(envp);
	if (!data.paths)
	{
		cleanup_data(&data);
		return (EXIT_FAILURE);
	}
	execute_pipex(&data);
	cleanup_data(&data);
	return (EXIT_SUCCESS);
}
