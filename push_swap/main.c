/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:11:16 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/03/19 15:52:44 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 1;
	if (ac >= 2)
	{
		while (i < ac)
		{
			if (check_if_numbers(av) == 1)
				return (1);
			if (has_spaces(av[i]))
			{
				if (check_doublon_string(av, &data) == 1)
					return (1);
			}
			else
				if (check_doublon(av, ac) == 1)
					return (1);
			i++;
		}
		// if (check_if_numbers(av) == 1)
		// 	return (1);
		// if (ac > 2)
		// {
		// 	if (check_doublon(av, ac) == 1)
		// 		return (1);
		// }
		// if (ac == 2)
		// {
		// 	if (check_doublon_string(av, &data) == 1)
		// 		return (1);
		// }
	}
	else
		ft_printf("Error\nVeuilez entrer 2 arguments minimum.\n");
	ft_printf("ok\n");
	return (0);
}
