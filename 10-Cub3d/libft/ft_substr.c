/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:09:00 by wlarbi-a          #+#    #+#             */
/*   Updated: 2024/11/23 09:45:13 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	if (ft_strlen(s) - start < len)
	{
		len = ft_strlen(s) - start;
	}
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	while (s[start] && i < len)
	{
		dest[i] = s[start];
		start++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
