/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 09:57:21 by flvejux           #+#    #+#             */
/*   Updated: 2026/01/06 09:59:36 by flvejux          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parse_arguments(int argc, char **argv, t_pipex *data)
{
	if (argc != 5)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (-1);
	}
	if (validate_files(argv[1], argv[4], data) == -1)
		return (-1);
	data->cmd1 = parse_command(argv[2]);
	if (!data->cmd1)
		return (-1);
	data->cmd2 = parse_command(argv[3]);
	if (!data->cmd2)
	{
		free_array(data->cmd1);
		return (-1);
	}
	return (0);
}

int	validate_files(char *infile, char *outfile, t_pipex *data)
{
	data->infile = open(infile, O_RDONLY);
	if (data->infile == -1)
	{
		ft_putstr_fd("Error: Can't open input file: ", 2);
		ft_putstr_fd(infile, 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	data->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile == -1)
	{
		ft_putstr_fd("Error: Can't open output file: ", 2);
		ft_putstr_fd(outfile, 2);
		ft_putstr_fd("\n", 2);
		close(data->infile);
		return (-1);
	}
	return (0);
}

char	**parse_command(char *cmd_str)
{
	char	**cmd_args;

	if (!cmd_str || !*cmd_str)
	{
		ft_putstr_fd("Error: Empty command\n", 2);
		return (NULL);
	}
	cmd_args = ft_split(cmd_str, ' ');
	if (!cmd_args || !cmd_args[0])
	{
		ft_putstr_fd("Error: Failed to parse command\n", 2);
		return (NULL);
	}
	return (cmd_args);
}
