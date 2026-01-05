/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 10:08:34 by flvejux           #+#    #+#             */
/*   Updated: 2026/01/05 10:08:38 by flvejux          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	child_process(t_pipex *data)
{
	char	*cmd_path;

	if (dup2(data->infile, STDIN_FILENO) == -1)
		error_exit("dup2 infile");
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
		error_exit("dup2 pipe write");
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	close(data->infile);
	close(data->outfile);
	cmd_path = find_command_path(data->cmd1[0], data->paths);
	if (!cmd_path)
	{
		ft_putstr_fd("Error: Command not found: ", 2);
		ft_putstr_fd(data->cmd1[0], 2);
		ft_putstr_fd("\n", 2);
		cleanup_data(data);
		exit(127);
	}
	if (execve(cmd_path, data->cmd1, data->envp) == -1)
	{
		free(cmd_path);
		cleanup_data(data);
		error_exit("execve cmd1");
	}
}

void	parent_process(t_pipex *data)
{
	char	*cmd_path;

	if (dup2(data->pipe_fd[0], STDIN_FILENO) == -1)
		error_exit("dup2 pipe read");
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		error_exit("dup2 outfile");
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	close(data->infile);
	close(data->outfile);
	cmd_path = find_command_path(data->cmd2[0], data->paths);
	if (!cmd_path)
	{
		ft_putstr_fd("Error: Command not found: ", 2);
		ft_putstr_fd(data->cmd2[0], 2);
		ft_putstr_fd("\n", 2);
		cleanup_data(data);
		exit(127);
	}
	if (execve(cmd_path, data->cmd2, data->envp) == -1)
	{
		free(cmd_path);
		cleanup_data(data);
		error_exit("execve cmd2");
	}
}

void	execute_pipex(t_pipex *data)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(data->pipe_fd) == -1)
		error_exit("pipe");
	pid1 = fork();
	if (pid1 == -1)
		error_exit("fork");
	if (pid1 == 0)
		child_process(data);
	pid2 = fork();
	if (pid2 == -1)
		error_exit("fork");
	if (pid2 == 0)
		parent_process(data);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	close(data->infile);
	close(data->outfile);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}
