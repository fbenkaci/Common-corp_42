/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wdmatch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:42:02 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/19 14:14:13 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int	len;
	int	i;
	int	j;

	if (ac == 3)
	{
		len = 0;
		j = 0;
		i = 0;
		while (av[1][len])
			len++;
		while (i < len && av[2][j])
		{
			if (av[1][i] == av[2][j])
				i++;
			j++;
		}
		if (i == len)
			write(1, av[1], len);
	}
	write(1, "\n", 1);
	return (0);
}
