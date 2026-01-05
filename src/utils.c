/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 09:50:10 by flvejux           #+#    #+#             */
/*   Updated: 2026/01/05 09:50:10 by flvejux          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/*
** cleanup_data - Cleans up all allocated resources
*/
void	cleanup_data(t_pipex *data)
{
	if (data->infile != -1)
		close(data->infile);
	if (data->outfile != -1)
		close(data->outfile);
	if (data->cmd1)
		free_array(data->cmd1);
	if (data->cmd2)
		free_array(data->cmd2);
	if (data->paths)
		free_array(data->paths);
}
