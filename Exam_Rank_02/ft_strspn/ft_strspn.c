/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:37:21 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/16 11:35:22 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

size_t	ft_strspn(const char *s, const char *accept)
{
	int		check;
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
        check = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
				check = 1;
			j++;
		}
		if (check == 0)
			return (i);
		i++;
	}
	return (i);
}

int	main(int ac, char **av)
{
	if (ac == 3)
	{
		printf("%zu\n", ft_strspn(av[1], av[2]));
		printf("%zu\n", strspn(av[1], av[2]));
	}

	return (0);
}