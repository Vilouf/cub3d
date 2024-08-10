/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_bis_x.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velbling <velbling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:55:38 by velbling          #+#    #+#             */
/*   Updated: 2024/08/10 19:55:43 by velbling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall_x(t_game *game, float *col, float y, float x)
{
	return ((game->map->map[(int)(y) / 64]
		[(int)(x + (col[0] * 4)) / 64] != '1' &&
		game->map->map[(int)(y + 24) / 64]
						[(int)(x + (col[0] * 4)) / 64] != '1' &&
		game->map->map[(int)(y - 24) / 64]
						[(int)(x + (col[0] * 4)) / 64] != '1' &&
		game->map->map[(int)(y + 12) / 64]
						[(int)(x + (col[0] * 4)) / 64] != '1' &&
		game->map->map[(int)(y - 12) / 64]
						[(int)(x + (col[0] * 4)) / 64] != '1'));
}

int	check_col_x_positive(t_game *game, float *col, float y, float x)
{
	return ((col[0] > 0
			&& (game->map->map[(int)(y) / 64]
			[(int)(x + (col[0] * 4) + 25) / 64] == '1'
		|| game->map->map[(int)(y + 24) / 64]
					[(int)(x + (col[0] * 4) + 25) / 64] == '1' ||
		game->map->map[(int)(y - 24) / 64]
					[(int)(x + (col[0] * 4) + 25) / 64] == '1' ||
		game->map->map[(int)(y + 12) / 64]
					[(int)(x + (col[0] * 4) + 25) / 64] == '1' ||
		game->map->map[(int)(y - 12) / 64]
					[(int)(x + (col[0] * 4) + 25) / 64] == '1')));
}

int	check_col_x_negative(t_game *game, float *col, float y, float x)
{
	return ((col[0] < 0
			&& (game->map->map[(int)(y) / 64]
			[(int)(x + (col[0] * 4) - 25) / 64] == '1'
		|| game->map->map[(int)(y + 24) / 64]
					[(int)(x + (col[0] * 4) - 25) / 64] == '1' ||
		game->map->map[(int)(y - 24) / 64]
					[(int)(x + (col[0] * 4) - 25) / 64] == '1' ||
		game->map->map[(int)(y + 12) / 64]
					[(int)(x + (col[0] * 4) - 25) / 64] == '1' ||
		game->map->map[(int)(y - 12) / 64]
					[(int)(x + (col[0] * 4) - 25) / 64] == '1')));
}
