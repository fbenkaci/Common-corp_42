/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:00:14 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/30 20:49:28 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int ac, char **av)
{
	int i;
	if (ac == 2)
	{
		i = 0;
		while (av[1][i] == ' ')
					i++;
		while (av[1][i])
		{
			if (av[1][i] == ' ')
			{
				while (av[1][i] == ' ')
					i++;
                if (av[1][i] != '\0')
				    write(1, " ", 1);
			}
            if (av[1][i] != '\0')
			    write(1, &av[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);

	return (0);
}