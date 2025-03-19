/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 08:53:01 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/14 09:16:38 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

char	*ft_strcpy(char *s1, char *s2)
{
    int i;

    i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
    s2[i] = '\0';
	return (s2);
}

int	main(void)
{
	char s1[10] = "helo";
	char s2[10];

	printf("%s", ft_strcpy(s1, s2));
}
