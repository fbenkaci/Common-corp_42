/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints_bits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:01:27 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/19 10:38:02 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	main(void)
{
	print_bits(2);

	return (0);
}