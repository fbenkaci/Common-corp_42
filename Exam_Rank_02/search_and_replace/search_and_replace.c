/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:09:22 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/15 10:33:24 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	if (argc == 4)
	{
		int i;
        
		i = 0;
		while (argv[1][i])
		{
            if (argv[2][1] != '\0' || argv[3][1] != '\0')
            {
	            write(1, "\n", 1);
                exit(1);
            }
			if (argv[1][i] == *argv[2])
				argv[1][i] = *argv[3];
			write(1, &argv[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);

	return (0);
}
