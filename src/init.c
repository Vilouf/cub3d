/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velbling <velbling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:18:40 by velbling          #+#    #+#             */
/*   Updated: 2024/08/13 20:51:35 by velbling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_map(void *param)
{
	t_game	*game;
	int		x;
	int		y;

	game = param;
	x = 0;
	y = 0;
	while (game->map->map[y])
	{
		while (game->map->map[x][y])
		{
			if (game->map->map[y][x] == 'E')
			{
				game->player->x_pos = (y * 64) + 24;
				game->player->y_pos = (x * 64) + 24;
				game->player->angle = 0;
			}
			x++;
		}
		y++;
	}
}

int	ft_load_png(t_game *game)
{
	game->n_txt = mlx_load_png(game->map->path_n);
	game->s_txt = mlx_load_png(game->map->path_s);
	game->e_txt = mlx_load_png(game->map->path_e);
	game->w_txt = mlx_load_png(game->map->path_w);
	if (game->w_txt == NULL || game->n_txt == NULL \
		|| game->s_txt == NULL || game->w_txt == NULL)
		return (0);
	return (1);
}
