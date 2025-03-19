/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:26:11 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/14 21:16:29 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// void	repeat_alpha(char *str)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] >= 'a' && str[i] <= 'z')
// 		{
// 			while (j < str[i] - 96)
// 			{
// 				write(1, &str[i], 1);
// 				j++;
// 			}
// 		}
// 		else if (str[i] >= 'A' && str[i] <= 'Z')
// 		{
// 			j = 0;
// 			while (j < str[i] - 64)
// 			{
// 				write(1, &str[i], 1);
// 				j++;
// 			}
// 		}
// 		else
// 			write(1, &str[i], 1);
// 		i++;
// 	}
//     write(1, "\n", 1);
// }

int	main(int argc, char **av)
{
	int	i;
	int	j;

	if (argc != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 0;
	while (av[1][i])
	{
		if (av[1][i] >= 'a' && av[1][i] <= 'z')
		{
			j = 0;
			while (j < av[1][i] - 96)
			{
				write(1, &av[1][i], 1);
				j++;
			}
		}
		else if (av[1][i] >= 'A' && av[1][i] <= 'Z')
		{
			j = 0;
			while (j < av[1][i] - 64)
			{
				write(1, &av[1][i], 1);
				j++;
			}
		}
		else
			write(1, &av[1][i], 1);
		i++;
	}
	write(1, "\n", 1);
}
