/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:45:00 by flvejux           #+#    #+#             */
/*   Updated: 2026/01/10 11:45:00 by flvejux          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	execute_command(t_pipex *data, char *cmd_str)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = parse_command(cmd_str);
	if (!cmd_args)
	{
		cleanup_data(data);
		error_exit("parse_command");
	}
	cmd_path = find_command_path(cmd_args[0], data->paths);
	if (!cmd_path)
	{
		ft_putstr_fd("Error: Command not found: ", 2);
		ft_putstr_fd(cmd_args[0], 2);
		ft_putstr_fd("\n", 2);
		free_array(cmd_args);
		cleanup_data(data);
		exit(127);
	}
	if (execve(cmd_path, cmd_args, data->envp) == -1)
	{
		free(cmd_path);
		free_array(cmd_args);
		cleanup_data(data);
		error_exit("execve");
	}
}

static void	handle_child(t_pipex *data, int input_fd, int pipe_fd[2],
						int is_last, char *cmd_str)
{
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			error_exit("dup2 input");
		close(input_fd);
	}
	if (is_last)
	{
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
			error_exit("dup2 outfile");
	}
	else
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			error_exit("dup2 pipe write");
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(data->outfile);
	execute_command(data, cmd_str);
}

void	execute_pipex(t_pipex *data, int argc, char **argv)
{
	int		i;
	int		input_fd;
	int		pipe_fd[2];
	pid_t	pid;

	i = (data->is_heredoc) ? 3 : 2;
	input_fd = data->infile;
	while (i < argc - 1)
	{
		if (pipe(pipe_fd) == -1)
			error_exit("pipe");
		pid = fork();
		if (pid == -1)
			error_exit("fork");
		if (pid == 0)
			handle_child(data, input_fd, pipe_fd, (i == argc - 2), argv[i]);
		close(pipe_fd[1]);
		if (input_fd != data->infile)
			close(input_fd);
		input_fd = pipe_fd[0];
		i++;
	}
	close(data->infile);
	close(data->outfile);
	while (waitpid(-1, NULL, 0) > 0)
		;
}
