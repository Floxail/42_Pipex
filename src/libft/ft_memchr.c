/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:22:40 by flvejux           #+#    #+#             */
/*   Updated: 2025/10/05 11:33:35 by flvejux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*us;
	unsigned char	uc;

	i = 0;
	us = (unsigned char *)s;
	uc = (unsigned char)c;
	while (i < n)
	{
		if (us[i] == uc)
			return ((void *)&us[i]);
		i++;
	}
	return (0);
}
