/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:27:42 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/20 12:35:31 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	putnbr(int nbr)
{
	unsigned	nb;

	nb = nbr;

	if (nb < 0)
		nb = -nb;
	else if(nb > 9)
	{
		putnbr(nb / 10);
		putnbr(nb % 10);
	}
	else
	{
		nb += 48;
		write(1, &nb, 1);
	}
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

int	estPremier(int nb)
{
	int	i;

	if (nb < 2)
		return (0);
	i = 2;
	while (i <= nb / 2)
	{
		if (nb % i == 0)
			return (0);
		i++;
	}
	return (1);
}

int	add_prime_sum(int nb)
{
	int	i;
	int	sum;

	i = 2;
	sum = 0;
	while (i <= nb)
	{
		if (estPremier(i) == 1)
			sum += i;
		i++;
	}
	return (sum);
}

int	main(int ac, char **av)
{
	int	n;

	if (ac != 2 || ft_atoi(av[1]) <= 1)
	{
		write(1, "0\n", 2);
		return (0);
	}
	n = ft_atoi(av[1]);
	putnbr(add_prime_sum(5));
	return (0);
}
