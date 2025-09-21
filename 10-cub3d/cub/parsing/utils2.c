/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:19:32 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/09/20 19:26:18 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	verif_file_name(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	while (i > 0 && str[i] != '.')
		i--;
	if (ft_strncmp(&str[i], ".cub", 5) == 0)
		return (1);
	printf("Error\nFile name must have .cub extension\n");
	return (0);
}

int	validate_color_line(char *line)
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

int	file_things(t_data *data)
{
	int		i;
	char	first_char;
	int		index;
	char	next_char;

	if (!check_texture_duplicates(data))
		return (0);
	i = -1;
	while (++i, data->file2[i] != NULL)
	{
		if (data->file2[i])
		{
			index = get_first_non_space_index(data->file2[i]);
			first_char = data->file2[i][index];
			next_char = data->file2[i][index + 1];
			if (!is_valid_texture_prefix(first_char, next_char))
			{
				printf("error, file2 not good\n");
				return (0);
			}
			if (!validate_texture_line(data->file2[i]))
				return (0);
		}
	}
	return (1);
}

int	check_texture_duplicates(t_data *data)
{
	int	counts[6];
	int	i;

	i = 0;
	while (i < 6)
		counts[i++] = 0;
	count_texture_identifiers(data, counts);
	if (counts[0] != 1 || counts[1] != 1 || counts[2] != 1 || counts[3] != 1
		|| counts[4] != 1 || counts[5] != 1)
	{
		printf("Error\nDuplicate or missing texture identifier\n");
		return (0);
	}
	return (1);
}
