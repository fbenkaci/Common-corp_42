/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase_x_maj.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:20:15 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/21 10:51:03 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbrbase_x_maj(unsigned int nb, unsigned int base)
{
	int					count;
	static const char	*base_16;

	count = 0;
	base_16 = "0123456789ABCDEF";
	if (nb < base)
	{
		count += ft_putchar(base_16[nb]);
		return (count);
	}
	else
	{
		count += ft_putnbrbase_x_maj((nb / base), base);
		count += ft_putnbrbase_x_maj((nb % base), base);
	}
	return (count);
}
