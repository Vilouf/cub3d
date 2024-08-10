/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_bis_y.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velbling <velbling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:08:22 by velbling          #+#    #+#             */
/*   Updated: 2024/08/10 20:00:29 by velbling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall_y(t_game *game, float *col, float y, float x)
{
	return ((game->map->map[(int)(y + (col[1] * 4)) / 64]
		[(int)(x) / 64] != '1' &&
		game->map->map[(int)(y + (col[1] * 4)) / 64]
					[(int)(x + 24) / 64] != '1' &&
		game->map->map[(int)(y + (col[1] * 4)) / 64]
					[(int)(x - 24) / 64] != '1' &&
		game->map->map[(int)(y + (col[1] * 4)) / 64]
					[(int)(x + 12) / 64] != '1' &&
		game->map->map[(int)(y + (col[1] * 4)) / 64]
					[(int)(x - 12) / 64] != '1'));
}

int	check_col_y_positive(t_game *game, float *col, float y, float x)
{
	return ((col[1] > 0
			&& (game->map->map[(int)(y + (col[1] * 4) + 25) / 64]
			[(int)(x) / 64] == '1'
		|| game->map->map[(int)(y + (col[1] * 4) + 25) / 64]
					[(int)(x + 24) / 64] == '1' ||
		game->map->map[(int)(y + (col[1] * 4) + 25) / 64]
					[(int)(x - 24) / 64] == '1' ||
		game->map->map[(int)(y + (col[1] * 4) + 25) / 64]
					[(int)(x + 12) / 64] == '1' ||
		game->map->map[(int)(y + (col[1] * 4) + 25) / 64]
					[(int)(x - 12) / 64] == '1')));
}

int	check_col_y_negative(t_game *game, float *col, float y, float x)
{
	return ((col[1] < 0
			&& (game->map->map[(int)(y + (col[1] * 4) - 25) / 64]
			[(int)(x) / 64] == '1'
		|| game->map->map[(int)(y + (col[1] * 4) - 25) / 64]
					[(int)(x + 24) / 64] == '1' ||
		game->map->map[(int)(y + (col[1] * 4) - 25) / 64]
					[(int)(x - 24) / 64] == '1' ||
		game->map->map[(int)(y + (col[1] * 4) - 25) / 64]
					[(int)(x + 12) / 64] == '1' ||
		game->map->map[(int)(y + (col[1] * 4) - 25) / 64]
					[(int)(x - 12) / 64] == '1')));
}
