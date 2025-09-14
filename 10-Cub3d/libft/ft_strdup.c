/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:41:06 by wlarbi-a          #+#    #+#             */
/*   Updated: 2024/11/16 10:19:10 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*des;
	int		i;

	i = 0;
	des = (char *)malloc(ft_strlen(src) * sizeof(char) + 1);
	if (!des)
		return (NULL);
	while (src[i])
	{
		des[i] = src[i];
		i++;
	}
	des[i] = '\0';
	return (des);
}
