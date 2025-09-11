/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:25:10 by wlarbi-a          #+#    #+#             */
/*   Updated: 2024/11/16 11:28:11 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *str, int n)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((char)n == str[i])
		{
			return ((char *)str + i);
		}
		i++;
	}
	if ((char)n == '\0')
	{
		return ((char *)str + i);
	}
	return (NULL);
}
