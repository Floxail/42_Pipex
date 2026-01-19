/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:01:27 by flvejux           #+#    #+#             */
/*   Updated: 2025/10/08 07:51:57 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*modstr;
	size_t	i;

	i = 0;
	modstr = malloc(sizeof(char) * ft_strlen(s) +1);
	if (!modstr)
		return (0);
	while (s[i])
	{
		modstr[i] = f(i, s[i]);
		i++;
	}
	modstr[i] = '\0';
	return (modstr);
}
