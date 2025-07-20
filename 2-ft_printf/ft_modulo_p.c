/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modulo_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:53:32 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/05 19:14:19 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// int	ft_modulo_p(unsigned long long nb, unsigned int base)
// {
// 	int		count;
// 	char	*Base;

// 	count = 0;
// 	Base = "0123456789abcdef";
// 	if (nb == 0)
// 		return (write(1, "(nil)", 5));
// 	count += ft_putstr("0x");
// 	if (nb < base)
// 	{
// 		ft_putchar(Base[nb]);
// 		count++;
// 		return (count);
// 	}
// 	else
// 	{
// 		count += ft_putNbrBase_x((nb / base), base);
// 		count += ft_putNbrBase_x((nb % base), base);
// 	}
// 	return (count);

int	ft_modulo_p(unsigned long long nb, unsigned int base)
{
	int		count;
	char	*base_16;

	count = 0;
	base_16 = "0123456789abcdef";
	if (!nb)
		return (write(1, "(nil)", 5));
	if (nb < base)
		count += ft_putstr("0x");
	if (nb >= base)
	{
		count += ft_modulo_p((nb / base), base);
	}
	count += ft_putchar(base_16[nb % base]);
	return (count);
}

// int main(void)
// {
//     char    *str;
//     char    a;

//     a = 98;
//     str = &a;
//     ft_printf("Mon modulo p [%p]\n", str);
//     printf("Le vrai [%p]", str);
//     return (0);
// }