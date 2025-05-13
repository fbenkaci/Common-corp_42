/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 01:16:33 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/13 01:16:36 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(char *str, int n)
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

char	*ft_strdup(char *src)
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

size_t	ft_strcpy(char *dst, char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}

size_t	ft_strcat(char *dst, char *src)
{
	size_t	i;
	size_t	len;


	len = ft_strlen(dst);
	i = 0;
	while (src[i] != '\0')
	{
		dst[len + i] = src[i];
		i++;
	}
	dst[len + i] = '\0';
	return (len + ft_strlen(src));
}
