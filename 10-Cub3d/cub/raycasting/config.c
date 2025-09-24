/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:56:24 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/09/13 18:57:25 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*get_texture_path_from_config(char **file2, const char *prefix)
{
	int	i;
	int	idx;

	i = 0;
	while (file2[i])
	{
		idx = 0;
		while (file2[i][idx] == ' ' || file2[i][idx] == '\t')
			idx++;
		if (ft_strncmp(&file2[i][idx], prefix, ft_strlen(prefix)) == 0)
		{
			idx += ft_strlen(prefix);
			while (file2[i][idx] == ' ' || file2[i][idx] == '\t')
				idx++;
			return (&file2[i][idx]);
		}
		i++;
	}
	return (NULL);
}

int	get_color_from_file2(char **file2, char identifier)
{
	int	i;
	int	idx;
	int	r;
	int	g;
	int	b;

	i = 0;
	while (file2[i])
	{
		idx = get_first_non_space_index(file2[i]);
		if (file2[i][idx] == identifier)
		{
			if (parse_color_line(file2[i], &r, &g, &b))
				return ((r << 16) | (g << 8) | b);
		}
		i++;
	}
	return (-1);
}
