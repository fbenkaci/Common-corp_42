/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:40:37 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/16 16:54:46 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int ac, char **av)
{
	if (ac == 3)
	{
		int check;
		int i;
		int j;

		check = 0;
		i = 0;
		j = 0;
		while (av[1][i])
		{
			j = 0;
			while (av[2][j])
			{
				if (av[1][i] == av[2][j])
				{
					write(1, &av[2][j], 1);
					break ;
				}
				j++;
			}
			i++;
		}
	}
	write(1, "\n", 1);

	return (0);
}