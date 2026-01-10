/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:40:00 by flvejux           #+#    #+#             */
/*   Updated: 2026/01/10 11:40:00 by flvejux          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	init_data(t_pipex *data)
{
	data->infile = -1;
	data->outfile = -1;
	data->envp = NULL;
	data->paths = NULL;
	data->is_heredoc = 0;
}

static int	setup_heredoc(t_pipex *data, int argc, char **argv)
{
	if (argc < 6)
	{
		ft_putstr_fd("Error: Invalid arguments for here_doc\n", 2);
		ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd1 cmd2 ... file\n", 2);
		return (-1);
	}
	data->is_heredoc = 1;
	data->infile = get_heredoc(argv[2]);
	if (data->infile == -1)
		return (-1);
	data->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (data->outfile == -1)
	{
		perror(argv[argc - 1]);
		close(data->infile);
		return (-1);
	}
	return (0);
}

static int	setup_normal(t_pipex *data, int argc, char **argv)
{
	if (argc < 5)
	{
		ft_putstr_fd("Error: Invalid arguments\n", 2);
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 ... file2\n", 2);
		return (-1);
	}
	data->is_heredoc = 0;
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile == -1)
	{
		perror(argv[1]);
		return (-1);
	}
	data->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->outfile == -1)
	{
		perror(argv[argc - 1]);
		close(data->infile);
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc < 5)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		return (EXIT_FAILURE);
	}
	init_data(&data);
	data.envp = envp;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		if (setup_heredoc(&data, argc, argv) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (setup_normal(&data, argc, argv) == -1)
			return (EXIT_FAILURE);
	}
	data.paths = get_paths(envp);
	if (!data.paths)
	{
		cleanup_data(&data);
		return (EXIT_FAILURE);
	}
	execute_pipex(&data, argc, argv);
	cleanup_data(&data);
	return (EXIT_SUCCESS);
}
