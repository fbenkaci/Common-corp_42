/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:44:21 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/09/10 14:24:01 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_texture_path(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] && line[i + 1] &&
		((line[i] == 'N' && line[i + 1] == 'O') ||
			(line[i] == 'S' && line[i + 1] == 'O') ||
			(line[i] == 'W' && line[i + 1] == 'E') ||
			(line[i] == 'E' && line[i + 1] == 'A')))
	{
		i += 2;
	}
	else if (line[i] && (line[i] == 'F' || line[i] == 'C'))
	{
		i += 1;
	}
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (&line[i]);
}

int	file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static char	*trim_spaces(char *str)
{
	char	*start;
	char	*end;
	int		len;
	char	*result;
	int		i;

	start = str;
	while (*start == ' ' || *start == '\t')
		start++;
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	len = end - start + 1;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = start[i];
		i++;
	}
	result[len] = '\0';
	return (result);
}

static int	is_valid_rgb_value(char *str)
{
	int	i;
	int	value;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	value = ft_atoi(str);
	return (value >= 0 && value <= 255);
}

int	parse_color_line(char *line, int *r, int *g, int *b)
{
	int		index;
	char	identifier;
	char	*color_part;
	char	**rgb_values;
	char	*trimmed;

	index = get_first_non_space_index(line);
	identifier = line[index];
	if (identifier != 'F' && identifier != 'C')
		return (0);
	index++;
	while (line[index] && (line[index] == ' ' || line[index] == '\t'))
		index++;
	color_part = &line[index];
	rgb_values = ft_split(color_part, ',');
	if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2]
		|| rgb_values[3])
	{
		free_split(rgb_values);
		return (0);
	}
	trimmed = trim_spaces(rgb_values[0]);
	if (!trimmed || !is_valid_rgb_value(trimmed))
	{
		free(trimmed);
		free_split(rgb_values);
		return (0);
	}
	*r = ft_atoi(trimmed);
	free(trimmed);
	trimmed = trim_spaces(rgb_values[1]);
	if (!trimmed || !is_valid_rgb_value(trimmed))
	{
		free(trimmed);
		free_split(rgb_values);
		return (0);
	}
	*g = ft_atoi(trimmed);
	free(trimmed);
	trimmed = trim_spaces(rgb_values[2]);
	if (!trimmed || !is_valid_rgb_value(trimmed))
	{
		free(trimmed);
		free_split(rgb_values);
		return (0);
	}
	*b = ft_atoi(trimmed);
	free(trimmed);
	free_split(rgb_values);
	return (1);
}

int	validate_color_line(char *line)
{
	int		index;
	char	identifier;

	index = get_first_non_space_index(line);
	identifier = line[index];
	int r, g, b;
	// Vérifier que c'est F ou C
	if (identifier != 'F' && identifier != 'C')
		return (1); // Pas une ligne de couleur
	// Parser la ligne
	if (!parse_color_line(line, &r, &g, &b))
	{
		printf("Error\nInvalid color format for %c\n", identifier);
		return (0);
	}
	printf("Parsed %c: RGB(%d, %d, %d)\n", identifier, r, g, b);
	return (1);
}

int	validate_texture_line(char *line)
{
	int		index;
	char	first_char;
	char	next_char;
	char	*path;

	index = get_first_non_space_index(line);
	first_char = line[index];
	next_char = line[index + 1];
	// Si c'est une couleur (F ou C), valider différemment
	if (first_char == 'F' || first_char == 'C')
	{
		return (validate_color_line(line));
	}
	// Sinon, valider comme texture
	if ((first_char == 'N' && next_char == 'O') ||
		(first_char == 'S' && next_char == 'O') ||
		(first_char == 'W' && next_char == 'E') ||
		(first_char == 'E' && next_char == 'A'))
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
