/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:02:21 by wlarbi-a          #+#    #+#             */
/*   Updated: 2024/11/16 12:26:18 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*s;
	unsigned char	t;

	s = (unsigned char *)str;
	t = (unsigned char)c;
	while (n > 0)
	{
		if (*s == t)
		{
			return (s);
		}
		s++;
		n--;
	}
	return (NULL);
}
