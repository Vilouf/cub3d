/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velbling <velbling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:49:52 by velbling          #+#    #+#             */
/*   Updated: 2024/08/12 19:07:46 by velbling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_extension_img(char *str, t_game *game)
{
	int	i;

	i = 0;
	if (game->argc != 2)
		error("Error wrong number of arguments", game);
	while (str[i])
		i++;
	if (str[i - 1] != 'g' || str[i - 2] != 'n' || str[i - 3] != 'p'
		|| str[i - 4] != '.')
		error("Error wrong extension for image file", game);
}

void	check_extension(char *str, t_game *game)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] != 'b' || str[i - 2] != 'u' || str[i - 3] != 'c'
		|| str[i - 4] != '.')
		error("Error wrong extension for map file", game);
}

void	before_check_img(t_game *game)
{
	if (game->free_n != 0)
		check_extension_img(game->map->path_n, game);
	if (game->free_s != 0)
		check_extension_img(game->map->path_s, game);
	if (game->free_e != 0)
		check_extension_img(game->map->path_e, game);
	if (game->free_w != 0)
		check_extension_img(game->map->path_w, game);
}

void	set_value(t_game *game, int argc, char	**argv)
{
	game->map->y_size = 0;
	game->map->x_size = 0;
	game->ceiling_r = -1;
	game->ceiling_g = -1;
	game->ceiling_b = -1;
	game->floor_r = -1;
	game->floor_g = -1;
	game->floor_b = -1;
	game->map->y = 0;
	game->map->x = 0;
	game->free = 0;
	game->free_n = 0;
	game->free_s = 0;
	game->free_e = 0;
	game->free_w = 0;
	game->j_rgb = 0;
	game->argv = argv;
	game->argc = argc;
	game->map->x = 0;
	game->map->y = 0;
	game->map->x_size = 0;
	game->map->y_size = 0;
}

int	main(int argc, char	**argv)
{
	t_game	game;
	int		i;

	game.map = malloc (sizeof(t_map));
	game.player = malloc (sizeof(t_player));
	game.ray = malloc (sizeof(t_ray));
	set_value(&game, argc, argv);
	check_extension(argv[1], &game);
	i = parsing(&game);
	before_check_img(&game);
	check_rgb(&game);
	map(&game, i);
	ft_load_png(&game);
	error_check(&game);
	mlx_loop_hook(game.mlx, ft_hook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_utils(&game);
	return (EXIT_SUCCESS);
}
