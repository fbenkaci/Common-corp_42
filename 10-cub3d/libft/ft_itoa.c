/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:35:15 by wlarbi-a          #+#    #+#             */
/*   Updated: 2024/11/18 16:45:12 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size(int n)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		i = 1;
	}
	else if (n < 0)
	{
		n = n * -1;
		i = 1;
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*dest;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = ft_size(n);
	dest = (char *)malloc(i + 1);
	if (!dest)
		return (NULL);
	dest[i] = '\0';
	if (n == 0)
		dest[0] = '0';
	else if (n < 0)
	{
		dest[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		dest[--i] = '0' + (n % 10);
		n = n / 10;
	}
	return (dest);
}
