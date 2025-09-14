/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:20:58 by wlarbi-a          #+#    #+#             */
/*   Updated: 2024/11/19 11:43:01 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_lst;
	t_list	*e;

	if (!lst || !f)
		return (NULL);
	n_lst = NULL;
	while (lst)
	{
		e = ft_lstnew((*f)(lst->content));
		if (!e)
		{
			while (n_lst)
			{
				e = n_lst->next;
				(*del)(n_lst->content);
				free(n_lst);
				n_lst = e;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&n_lst, e);
		lst = lst->next;
	}
	return (n_lst);
}
