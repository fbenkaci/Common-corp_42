/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 09:47:35 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/16 10:36:15 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

size_t	ft_strcspn(const char *s, const char *reject)
{
    size_t i;
    size_t j;

    i = 0;
    while (s[i])
    {
        j = 0;
        while (reject[j])
        {
            if (s[i] == reject[j])
                return (i);
            j++;
        }
        i++;
    }
    return (i);
}

int main(int ac, char **av)
{
    if (ac == 3)
    {
        printf("Le mien %zu\n", ft_strcspn(av[1], av[2]));
        printf("Le sien %zu", strcspn(av[1], av[2]));
    }
    printf("\n");
    
    return (0);
}