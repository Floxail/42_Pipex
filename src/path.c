/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 09:31:21 by flvejux           #+#    #+#             */
/*   Updated: 2026/01/05 09:35:20 by flvejux          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** get_paths - Extracts PATH variable from environment
** Searches for "PATH=" in envp and splits by ':'
** Returns: Array of paths or NULL if not found
*/
char	**get_paths(char **envp)
{
	int		i;
	char	*path_line;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_line = envp[i] + 5;
			paths = ft_split(path_line, ':');
			return (paths);
		}
		i++;
	}
	ft_putstr_fd("Error: PATH not found in environment\n", 2);
	return (NULL);
}

char	*find_command_path(char *cmd, char **paths)
{
	int		i;
	char	*full_path;
	char	*temp;

	if (!cmd || !paths)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
