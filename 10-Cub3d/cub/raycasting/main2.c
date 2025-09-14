/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:30:23 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/09/13 19:14:20 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_game_and_data(t_game *game, t_data *data)
{
	int	i;

	i = 0;
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->data_img = NULL;
	game->ray = NULL;
	game->data.map = NULL;
	game->data.file2 = NULL;
	game->data.file = NULL;
	game->close = 0;
	game->camera_x = 0.0;
	while (i < 4)
	{
		game->texture[i].img = NULL;
		i++;
	}
	data->map = NULL;
	data->file2 = NULL;
	data->file = NULL;
	data->player.x = 0;
	data->player.y = 0;
}

static int	handle_file_input(int argc, char **argv, t_data *data)
{
	char	*file_content;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (0);
	}
	if (!validate_file_format(argv[1]))
	{
		printf("Erreur : format de fichier invalide\n");
		return (0);
	}
	file_content = gnl_img(argv[1]);
	if (!file_content)
	{
		printf("Erreur : impossible de lire le fichier\n");
		return (0);
	}
	data->file = ft_split(file_content, '\n');
	free(file_content);
	if (!data->file)
		return (printf("Erreur : impossible de traiter le fichier\n"), 0);
	return (1);
}

static int	handle_map(t_data *data)
{
	map(data);
	if (ft_verif(*data) == 0)
	{
		printf("Erreur map\n");
		free_char_tab(data->file);
		free_char_tab(data->file2);
		free_char_tab(data->map);
		return (0);
	}
	if (!data->file2)
	{
		printf("Erreur : données de configuration manquantes\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_data	data;

	init_game_and_data(&game, &data);
	if (!handle_file_input(argc, argv, &data))
		return (1);
	if (!handle_map(&data))
		return (1);
	game.data = data;
	init_game(&game, data.file2);
	if (!game.mlx || !game.win || !game.img || !game.ray)
	{
		printf("Erreur : initialisation du jeu échouée\n");
		cleanup(&game);
		return (1);
	}
	mlx_hook(game.win, 2, 1 << 0, key_press, &game);
	mlx_hook(game.win, 3, 1 << 1, key_release, &game.player);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
