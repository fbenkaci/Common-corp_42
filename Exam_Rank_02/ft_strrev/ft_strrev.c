/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:07:20 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/16 16:37:21 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strrev(char *str)
{
	char	tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (str[i])
		i++;
    i--;
	while (j < i)
	{
        tmp = str[j];
		str[j] = str[i];
        str[i] = tmp;
		j++;
		i--;
	}
	return (str);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		printf("%s", ft_strrev(av[1]));
	}

	return (0);
}