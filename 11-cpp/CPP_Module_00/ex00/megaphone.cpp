/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:07:24 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/09/25 15:14:52 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cctype>
#include <iostream>

int	main(int ac, char **av)
{
	if (ac > 1)
	{
		for (int j = 1; av[j]; j++)
		{
			for (int i = 0; av[j][i]; i++)
			{
                if (islower(av[j][i]))
                    av[j][i] = toupper(av[j][i]);
                std::cout << av[j][i];
			}
		}
        std::cout << std::endl;
	}
	else
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	return (0);
}
