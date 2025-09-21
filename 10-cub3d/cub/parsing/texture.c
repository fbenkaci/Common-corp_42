/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 19:11:16 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/09/14 19:11:56 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_table_of_table(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		ft_putendl_fd(table[i++], 1);
}

int	count_texture_lines(t_data *data)
{
	int		i;
	int		texture;
	char	first_char;

	texture = 0;
	i = 0;
	while (data->file[i])
	{
		first_char = get_first_non_space_char(data->file[i]);
		if (first_char == 'N' || first_char == 'S' || first_char == 'W'
			|| first_char == 'E' || first_char == 'F' || first_char == 'C')
		{
			texture++;
		}
		else if (first_char != '\0')
		{
			break ;
		}
		i++;
	}
	return (texture);
}

int	extract_textures(t_data *data)
{
	int	i;
	int	j;
	int	texture;

	texture = count_texture_lines(data);
	data->file2 = malloc(sizeof(char *) * (texture + 1));
	j = 0;
	while (j < texture)
	{
		data->file2[j] = ft_strdup(data->file[j]);
		j++;
	}
	data->file2[texture] = NULL;
	i = 0;
	while (data->file[i] && i < texture)
		i++;
	while (data->file[i] && get_first_non_space_char(data->file[i]) == '\0')
		i++;
	return (i);
}

void	extract_map(t_data *data, int map_start)
{
	int	i;
	int	j;

	j = 0;
	while (data->file[map_start + j])
		j++;
	data->map = malloc(sizeof(char *) * (j + 1));
	if (!data->map)
		return ;
	i = 0;
	while (data->file[map_start + i])
	{
		data->map[i] = ft_strdup(data->file[map_start + i]);
		i++;
	}
	data->map[i] = NULL;
}

void	map(t_data *data)
{
	int	map_start;

	map_start = extract_textures(data);
	extract_map(data, map_start);
}
