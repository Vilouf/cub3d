/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velbling <velbling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:01:33 by velbling          #+#    #+#             */
/*   Updated: 2024/08/10 19:49:01 by velbling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	collision_y(t_game *game, float col[2], float x, float y)
{
	int	t;

	t = 0;
	if (check_wall_y(game, col, y, x))
	{
		if (check_col_y_positive(game, col, y, x))
			t = 1;
		if (check_col_y_negative(game, col, y, x))
			t = 1;
	}
	if (!t)
		game->player->y_pos += 4 * col[1];
}

void	collision_x(t_game *game, float col[2], float x, float y)
{
	int	t;

	t = 0;
	if (check_wall_x(game, col, y, x))
	{
		if (check_col_x_positive(game, col, y, x))
			t = 1;
		if (check_col_x_negative(game, col, y, x))
			t = 1;
	}
	if (!t)
		game->player->x_pos += 4 * col[0];
	collision_y(game, col, game->player->x_pos, game->player->y_pos);
}

static void	ft_movement(t_game *game)
{
	float	col[2];

	col[0] = 0;
	col[1] = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		col[0] += cos(game->player->angle);
		col[1] += sin(game->player->angle);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		col[0] += -cos(game->player->angle);
		col[1] += -sin(game->player->angle);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		col[0] += sin(game->player->angle);
		col[1] += -cos(game->player->angle);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		col[0] += -sin(game->player->angle);
		col[1] += cos(game->player->angle);
	}
	collision_x(game, col, game->player->x_pos, game->player->y_pos);
}

void	ft_hook(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	ft_movement(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->player->angle += M_PI / 32;
		if (game->player->angle > 4 * M_PI)
			game->player->angle -= 4 * M_PI;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->player->angle -= M_PI / 32;
		if (game->player->angle < 0)
			game->player->angle += 4 * M_PI;
	}
	put_image(game);
}
