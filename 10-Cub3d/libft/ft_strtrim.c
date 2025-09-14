/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:22:46 by wlarbi-a          #+#    #+#             */
/*   Updated: 2024/11/19 13:36:04 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
		{
			return (1);
		}
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	s;
	size_t	e;
	char	*dest;

	i = 0;
	while (s1[i] && is_in_set(s1[i], set))
		i++;
	s = ft_strlen(s1);
	while (s > i && is_in_set(s1[s - 1], set))
		s--;
	e = s;
	if (i >= e)
		return (ft_strdup(""));
	dest = (char *)malloc(e - i + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s1[i], e - i + 1);
	return (dest);
}
