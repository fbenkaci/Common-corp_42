/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:36:24 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/16 12:11:57 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char *dst;
	int i;
    
	dst = malloc((ft_strlen(src) + 1) * sizeof(src));
	if (!dst)
		return (NULL);
	while (src[i])
	{
        dst[i] = src[i];
        i++;
	}
    dst[i] = '\0';
}