/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_error3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:08:05 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/09/14 19:12:45 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_texture_path(char first_char, char next_char, char *line)
{
	char	*path;

	if ((first_char == 'N' && next_char == 'O') || (first_char == 'S'
			&& next_char == 'O') || (first_char == 'W' && next_char == 'E')
		|| (first_char == 'E' && next_char == 'A'))
	{
		path = get_texture_path(line);
		if (!path || *path == '\0')
		{
			printf("Error\nMissing texture path\n");
			return (0);
		}
		if (!file_exists(path))
		{
			printf("Error\nTexture file not found: %s\n", path);
			return (0);
		}
	}
	return (1);
}

int	validate_texture_line(char *line)
{
	int		index;
	char	first_char;
	char	next_char;

	index = get_first_non_space_index(line);
	first_char = line[index];
	next_char = line[index + 1];
	if (first_char == 'F' || first_char == 'C')
	{
		return (validate_color_line(line));
	}
	return (validate_texture_path(first_char, next_char, line));
}

int	check_texture_after_map(char *str, int i, int in_map_section)
{
	if (in_map_section && (i == 0 || str[i - 1] == '\n'))
	{
		if (is_texture_char(str[i]))
		{
			printf("Error\nTexture definition after map\n");
			return (0);
		}
	}
	return (1);
}

int	validate_file_format(char *str)
{
	int	i;
	int	in_map_section;

	i = 0;
	in_map_section = 0;
	while (str[i])
	{
		if (!in_map_section && (i == 0 || str[i - 1] == '\n'))
		{
			if (is_map_line(str, i))
				in_map_section = 1;
		}
		if (in_map_section && is_empty_line_in_map(str, i))
		{
			printf("Error\nEmpty line in map section\n");
			return (0);
		}
		if (!check_texture_after_map(str, i, in_map_section))
			return (0);
		i++;
	}
	return (1);
}

void	free_char_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
