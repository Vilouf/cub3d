/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velbling <velbling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:01:33 by velbling          #+#    #+#             */
/*   Updated: 2024/05/04 16:16:31 by velbling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static int	ft_is_movement(mlx_t *mlx)
// {
// 	return(mlx_is_key_down(mlx, MLX_KEY_W) 
// 		|| mlx_is_key_down(mlx, MLX_KEY_S)
// 		|| mlx_is_key_down(mlx, MLX_KEY_A)
// 		|| mlx_is_key_down(mlx, MLX_KEY_D)
// 		|| mlx_is_key_down(mlx, MLX_KEY_RIGHT)
// 		|| mlx_is_key_down(mlx, MLX_KEY_LEFT));
// }

// int	collision(t_game *game, float x_pos, float y_pos)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < game->map->y_size)
// 	{
// 		x = 0;
// 		while (game->map->map[y][x])
// 		{
// 			if (game->map->map[y][x] == '1')
// 			{
// 				if (y_pos <= (float) y * 64 + 64 
// 					&& y_pos >= (float) y * 64 
// 					&& x_pos <= (float) x * 64 + 64 
// 					&& x_pos >= (float) x * 64)
// 				{
// 					return (0);
// 				}
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (1);
// }

static void	ft_movement(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W)/* && collision(game, game->player->x_pos -= 2 * -cos(game->player->angle), game->player->y_pos -= 2 * -sin(game->player->angle))*/)
	{
		game->player->x_pos -= 4 * -cos(game->player->angle);
		game->player->y_pos -= 4 * -sin(game->player->angle);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->player->x_pos += 4 * -cos(game->player->angle);
		game->player->y_pos += 4 * -sin(game->player->angle);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->player->x_pos -= 4 * -sin(game->player->angle);
		game->player->y_pos -= 4 * cos(game->player->angle);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->player->x_pos += 4 * -sin(game->player->angle);
		game->player->y_pos += 4 * cos(game->player->angle);
	}
}

void	ft_hook(void* param)
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
