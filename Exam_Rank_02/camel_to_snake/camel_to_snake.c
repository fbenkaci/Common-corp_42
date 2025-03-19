/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camel_to_snake.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:35:23 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/15 12:07:45 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include  <stdlib.h>

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		int i;

	    i = 0;
        while (av[1][i])
		{
            if (av[1][i] >= 'A' && av[1][i] <= 'Z')
            {
                av[1][i] += 32;
                write(1, "_", 1);
            }
            write(1, &av[1][i], 1);
            i++;
		}
	}
	write(1, "\n", 1);

	return (0);
}