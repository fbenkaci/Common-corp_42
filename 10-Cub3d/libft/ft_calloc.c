/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:49:13 by wlarbi-a          #+#    #+#             */
/*   Updated: 2024/11/27 09:36:05 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*src;
	size_t	len;

	if (count && size > (size_t)-1 / count)
		return (NULL);
	len = count * size;
	src = (void *)malloc(len);
	if (!src)
		return (NULL);
	ft_memset(src, 0, len);
	return (src);
}
