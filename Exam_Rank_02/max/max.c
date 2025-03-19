/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:40:00 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/16 21:00:27 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> 

int	max(int *tab, unsigned int len)
{
	int	max;
	unsigned int	i;

	if (len == 0)
		return (0);
    i = 0;
	max = tab[0];
	while (i < len)
	{
        if (max < tab[i])
            max = tab[i];
        i++;
    }
	return (max);
}

int main(void)
{
    int tab[10] = {999999991, 10, 20 , 30, 1000000, 99999999};
    int len;
    len = sizeof(tab) / sizeof(int);
    printf("%d", max(tab, len));
    
    return (0);
} 