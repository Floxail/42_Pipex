/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flox <flox@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:09:20 by flvejux           #+#    #+#             */
/*   Updated: 2025/10/10 12:41:54 by flox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	nb_size(long n)
{
	size_t	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		size++;
	}
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long	nbr;
	size_t	len;
	size_t	i;
	char	*nb;

	i = 0;
	nbr = (long)n;
	len = nb_size(nbr);
	nb = malloc(sizeof(char) * (len + 1));
	if (!nb)
		return (0);
	nb[len] = '\0';
	if (n == 0)
		nb[i] = '0';
	if (nbr < 0)
	{
		nb[0] = '-';
		nbr *= -1;
	}
	while (nbr != 0)
	{
		nb[(len - 1) - i++] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (nb);
}
