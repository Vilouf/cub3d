/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velbling <velbling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:18:40 by velbling          #+#    #+#             */
/*   Updated: 2024/05/04 15:56:14 by velbling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_init_map(void* param)
{
	t_game *game;

	game = param;

	for (int x = 0; game->map->map[x]; x++)
	{
		for (int y = 0; game->map->map[x][y]; y++)
		{
			// if (game->map->map[x][y] == '1')
			// {
			// 	spread_pixels(game, y * 64, x * 64, 0xFFAA00FF);
			// }
			if (game->map->map[x][y] == 'E')
			{
				game->player->x_pos = (y * 64) + 24;
				game->player->y_pos = (x * 64) + 24;
				game->player->angle = 0;
				// init_player_pos(game);
			}
		}
	}
}

void	ft_load_png(t_game * game)
{
	game->n_txt = mlx_load_png(game->map->path_n);
	game->s_txt = mlx_load_png(game->map->path_s);
	game->e_txt = mlx_load_png(game->map->path_e);
	game->w_txt = mlx_load_png(game->map->path_w);
}
