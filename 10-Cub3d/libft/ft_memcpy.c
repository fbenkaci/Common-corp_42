/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:06:30 by wlarbi-a          #+#    #+#             */
/*   Updated: 2024/11/18 16:45:26 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t				i;
	unsigned char		*f;
	const unsigned char	*s;

	s = (unsigned char *)src;
	i = 0;
	f = (unsigned char *)dest;
	if (!dest && !src)
		return (NULL);
	while (i < size)
	{
		f[i] = s[i];
		i++;
	}
	return (f);
}
