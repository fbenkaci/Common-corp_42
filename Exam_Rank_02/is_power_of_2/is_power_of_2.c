/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_power_of_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:06:09 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/16 20:39:19 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	    is_power_of_2(unsigned int n)
{
    unsigned int a;

    a = 1;    
    while (a <= n)
    {
        if (a == n)
            return (1);    
        a *= 2;
    }
    return (0);
}

int main(int ac, char **av)
{
    if (ac == 2)
    {
        printf("%d", is_power_of_2(atoi(av[1])));
    }
    
    return (0);
}