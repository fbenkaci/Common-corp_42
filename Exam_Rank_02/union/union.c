/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:53:33 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/20 09:35:22 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int ac, char **av)
{
	int i;
	int j;
	int found;

	if (ac == 3)
	{
		i = 0;
		while (av[1][i])
		{
		    found = 0;
			j = 0;
			while (av[2][j])
			{
				if (av[1][i] == av[2][j])
				{
                    found = 1;
                    break ;
                }
                j++;
			}
			if (!found)
				write(1, &av[1][i], 1);
                
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}