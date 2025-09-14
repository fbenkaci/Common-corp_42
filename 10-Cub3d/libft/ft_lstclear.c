/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:02:39 by wlarbi-a          #+#    #+#             */
/*   Updated: 2024/11/19 11:17:52 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*s;
	t_list	*slt;

	s = *lst;
	while (s)
	{
		slt = s->next;
		ft_lstdelone(s, del);
		s = slt;
	}
	*lst = NULL;
}
