/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:50:00 by flvejux           #+#    #+#             */
/*   Updated: 2026/01/10 11:50:00 by flvejux          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
