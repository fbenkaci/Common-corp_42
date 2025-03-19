/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:09:39 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/21 09:48:27 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	*ft_range(int start, int end)
{
	int	len;
	int	*tab;
	int	temp;
	int	i;

	temp = start;
	len = 0;
	i = 0;
    if (start < end )
    {
        while (start < end)
        {
            len++;
            start++;
        }
    }
    else
    {
        while (start > end)
        {
            len++;
            start--;
        }
    }
    
	tab = malloc(len * sizeof(int));
	if (!tab)
		return (0);
	while (i <= len)
	{
		if (temp < end)
			tab[i] = temp++;
		else
			tab[i] = temp--;
		printf("%d\n", tab[i]);
		i++;
	}
	return (0);
}

int	main(void)
{
	ft_range(0, -3);

	return (0);
}