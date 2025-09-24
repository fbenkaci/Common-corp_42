/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:03:30 by wlarbi-a          #+#    #+#             */
/*   Updated: 2024/11/12 16:32:42 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int n)
{
	size_t	i;

	i = ft_strlen(s);
	while (i > 0)
	{
		if ((unsigned char)n == (unsigned char)s[i])
		{
			return ((char *)s + i);
		}
		i--;
	}
	if ((unsigned char)n == (unsigned char)s[i])
	{
		return ((char *)s + i);
	}
	return (NULL);
}
