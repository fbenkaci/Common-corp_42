/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:44:43 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/21 08:57:39 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	ft_is_valid(char c, int base)
{
	int		i;
	char	digit_l[17] = "0123546789abcdef";
	char	digit_u[17] = "0123546789ABCDEF";

	i = 0;
	while (i < base)
	{
		if (digit_l[i] == c || digit_u[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_value_of(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	result;
	int	sign;
	int	i;

	i = 0;
	result = 0;
	sign = 1;
	while (*str == ' ')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	while (ft_is_valid(*str, str_base))
	{
		result = result * str_base + ft_value_of(*str);
		str++;
	}
	return (result * sign);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	if (ac == 3)
	{
		printf("%d", ft_atoi_base(av[1], ft_atoi_base(av[2], 10)));
		return (0);
	}
	return (0);
}
