/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:38:22 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/21 12:04:15 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	*ft_rrange(int start, int end)
{
	int	len;
	int	*tab;
	int	i;

	len = (start <= end) ? (end - start + 1) : (start - end + 1);
	tab = malloc(len * sizeof(int));
	if (!tab)
		return (NULL);
	i = 0;
	if (start <= end)
	{
		while (end >= start)
        {
			tab[i] = end--;
            printf("%d\n", tab[i]);
            i++;
        }
	}
	else
	{
		while (end <= start)
		{
            tab[i] = end++;
            printf("%d\n", tab[i]);
            i++;
        }
    }
	return (tab);
}

int	main(void)
{
	ft_rrange(0, -3);
	return (0);
}
