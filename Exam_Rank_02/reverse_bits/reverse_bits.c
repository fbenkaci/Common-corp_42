/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 10:11:54 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/19 12:39:11 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	print_bits(unsigned char octet)
{
	char	bits;
	int		i;

	i = 7;
	while (i >= 0)
	{
		bits = ((octet >> i) & 1) + '0';
		write(1, &bits, 1);
		i--;
	}
}

unsigned char	reverse_bits(unsigned char octet)
{
	unsigned char	result;
	int				i;

	result = 0;
	i = 0;
	while (i < 8)
	{
		result = (result << 1) | (octet & 1);
		octet >>= 1;
		i++;
	}
	return (result);
}

int	main(void)
{
	unsigned char octet;

octet = 0b0000011;
	print_bits(reverse_bits(octet));

	return (0);
}
