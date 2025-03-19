/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:27:49 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/20 12:20:51 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_atoi(const char *str)
{
	int result;
	int sign;
    int i;
    
    result = 0;
    sign = 1;
	i = 0;
    if (str[i] == '-')
    {
        sign *= -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
        result = result * 10 + str[i] - 48;
        i++;
    }
    return (result * sign);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (0);
    printf("%d\n", ft_atoi(argv[1]));

    return (0);
}