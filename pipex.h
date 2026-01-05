/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:51:22 by flvejux           #+#    #+#             */
/*   Updated: 2026/01/05 11:52:01 by flvejux          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "libft/libft.h"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**cmd1;
	char	**cmd2;
	char	**envp;
	char	**paths;
	int		pipe_fd[2];
}	t_pipex;

/* Parsing */
int		parse_arguments(int argc, char **argv, t_pipex *data);
int		validate_files(char *infile, char *outfile, t_pipex *data);
char	**parse_command(char *cmd_str);

/* Path handling */
char	**get_paths(char **envp);
char	*find_command_path(char *cmd, char **paths);

/* Process execution */
void	execute_pipex(t_pipex *data);
void	child_process(t_pipex *data);
void	parent_process(t_pipex *data);

/* Utils */
void	error_exit(char *msg);
void	free_array(char **array);
void	cleanup_data(t_pipex *data);

#endif