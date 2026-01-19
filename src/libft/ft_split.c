/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flox <flox@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 08:49:17 by flvejux           #+#    #+#             */
/*   Updated: 2025/10/10 11:55:07 by flox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_len(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	ft_count_words(const char *str, char c)
{
	int	words;

	words = 0;
	while (*str)
	{
		if (*str != c)
		{
			words++;
			str += ft_word_len(str, c);
		}
		if (*str == c)
			str++;
	}
	return (words);
}

static void	ft_free(char **str, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(str[i]);
		i++;
	}
	free (str);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;

	i = 0;
	strs = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!strs)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			strs[i] = malloc(ft_word_len(s, c) + 1);
			if (!strs[i])
				ft_free(strs, i);
			ft_strlcpy(strs[i], s, ft_word_len(s, c) + 1);
			s += ft_word_len(s, c);
			i++;
		}
		while (*s && *s == c)
			s++;
	}
	strs[i] = 0;
	return (strs);
}
