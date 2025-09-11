/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:24:19 by wlarbi-a          #+#    #+#             */
/*   Updated: 2024/11/12 16:01:09 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t l)
{
	size_t	i;

	i = 0;
	if (l == 0)
		return (0);
	while (s1[i] && s2[i] && s2[i] == s1[i] && i < l)
	{
		i++;
	}
	if (i == l)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
