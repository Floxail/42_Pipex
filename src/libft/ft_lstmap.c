/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floxail <floxail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:43:18 by flox              #+#    #+#             */
/*   Updated: 2025/10/13 09:53:07 by floxail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*newlst;

	tmp = 0;
	while (lst)
	{
		newlst = ft_lstnew((f)(lst->content));
		if (!newlst)
		{
			ft_lstclear(&lst, (*del));
			return (0);
		}
		ft_lstadd_back(&tmp, newlst);
		lst = lst->next;
	}
	return (tmp);
}
