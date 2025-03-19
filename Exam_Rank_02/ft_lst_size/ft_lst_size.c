/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:00:46 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/21 09:08:26 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

int	ft_list_size(t_list *begin_list)
{
    int i;

    i = 0;
    while (begin_list->next)
    {
        begin_list = begin_list->next;
        i++;
    }
    return (i); 
}