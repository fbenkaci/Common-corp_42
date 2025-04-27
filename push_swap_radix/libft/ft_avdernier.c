/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_avdernier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:11:44 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/27 15:41:30 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_avdernier(t_list *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	while (lst->next->next != NULL)
		lst = lst->next;
	return (lst);
}
