/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:48:44 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/16 12:17:04 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	last_word(char *str)
{
	int	i;

	i = 0;
    while (str[i])
        i++;
    i--;
    while (str[i] <= 32)
        i--;
    while (str[i] > 32)
        i--;
    i++;
    while (str[i] > 32)
    {
        write(1, &str[i], 1);
        i++;
    }
    write (1, "\n", 1);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		last_word(av[1]);
	}

	return (0);
}