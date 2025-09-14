/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 08:29:43 by wlarbi-a          #+#    #+#             */
/*   Updated: 2024/11/15 11:56:13 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *dest, int c, size_t count)
{
	size_t	i;
	char	*src;

	src = (char *)dest;
	i = 0;
	while (i < count)
	{
		src[i] = c;
		i++;
	}
	return (src);
}
