/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:44:21 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/09/20 19:24:24 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_single_rgb(char *rgb_str, int *value)
{
	char	*trimmed;

	trimmed = trim_spaces(rgb_str);
	if (!trimmed || !is_valid_rgb_value(trimmed))
	{
		free(trimmed);
		return (0);
	}
	*value = ft_atoi(trimmed);
	free(trimmed);
	return (1);
}

int	parse_rgb_values(char **rgb_values, int *r, int *g, int *b)
{
	if (!parse_single_rgb(rgb_values[0], r))
		return (0);
	if (!parse_single_rgb(rgb_values[1], g))
		return (0);
	if (!parse_single_rgb(rgb_values[2], b))
		return (0);
	return (1);
}

char	*extract_color_part(char *line)
{
	int		index;
	char	identifier;

	index = get_first_non_space_index(line);
	identifier = line[index];
	if (identifier != 'F' && identifier != 'C')
		return (NULL);
	index++;
	while (line[index] && (line[index] == ' ' || line[index] == '\t'))
		index++;
	return (&line[index]);
}

int	parse_color_line(char *line, int *r, int *g, int *b)
{
	char	*color_part;
	char	**rgb_values;

	color_part = extract_color_part(line);
	if (!color_part)
		return (0);
	rgb_values = ft_split(color_part, ',');
	if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2]
		|| rgb_values[3])
	{
		free_split(rgb_values);
		return (0);
	}
	if (!parse_rgb_values(rgb_values, r, g, b))
	{
		free_split(rgb_values);
		return (0);
	}
	free_split(rgb_values);
	return (1);
}

int	_color_line(char *line)
{
	int		index;
	char	identifier;
	int		r;
	int		g;
	int		b;

	index = get_first_non_space_index(line);
	identifier = line[index];
	if (identifier != 'F' && identifier != 'C')
		return (1);
	if (!parse_color_line(line, &r, &g, &b))
	{
		printf("Error\nInvalid color format for %c\n", identifier);
		return (0);
	}
	return (1);
}
