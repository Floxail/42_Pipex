/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_herdoc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:20:20 by flvejux           #+#    #+#             */
/*   Updated: 2026/01/10 10:20:55 by flvejux          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*read_line(void)
{
	char	*line;
	char	buffer;
	int		i;
	int		ret;

	line = malloc(1024);
	if (!line)
		return (NULL);
	i = 0;
	ret = read(STDIN_FILENO, &buffer, 1);
	while (ret > 0 && buffer != '\n' && i < 1023)
	{
		line[i++] = buffer;
		ret = read(STDIN_FILENO, &buffer, 1);
	}
	line[i] = '\0';
	if (ret <= 0 && i == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	get_heredoc(char *limiter)
{
	int		fd_heredoc[2];
	char	*line;

	if (pipe(fd_heredoc) == -1)
		error_exit("pipe");
	write(STDOUT_FILENO, "heredoc> ", 9);
	line = read_line();
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(line) == ft_strlen(limiter))
		{
			free(line);
			break ;
		}
		write(fd_heredoc[1], line, ft_strlen(line));
		write(fd_heredoc[1], "\n", 1);
		free(line);
		write(STDOUT_FILENO, "heredoc> ", 9);
		line = read_line();
	}
	close(fd_heredoc[1]);
	return (fd_heredoc[0]);
}