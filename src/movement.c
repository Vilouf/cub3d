/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velbling <velbling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:01:33 by velbling          #+#    #+#             */
/*   Updated: 2024/08/06 19:21:47 by velbling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void collision_y(t_game *game, float col[2], float x, float y)
{
    int t = 0;

    // Vérifie les quatre coins et les positions adjacentes pour les collisions potentielles en Y
    if (game->map->map[(int)(y + (col[1] * 4)) / 64][(int)(x) / 64] != '1' &&
        game->map->map[(int)(y + (col[1] * 4)) / 64][(int)(x + 24) / 64] != '1' &&
        game->map->map[(int)(y + (col[1] * 4)) / 64][(int)(x - 24) / 64] != '1' &&
        game->map->map[(int)(y + (col[1] * 4)) / 64][(int)(x + 12) / 64] != '1' &&
        game->map->map[(int)(y + (col[1] * 4)) / 64][(int)(x - 12) / 64] != '1')
    {
        // Vérifie les collisions potentielles près de la boîte englobante du joueur
        if (col[1] > 0 && (game->map->map[(int)(y + (col[1] * 4) + 25) / 64][(int)(x) / 64] == '1' ||
                           game->map->map[(int)(y + (col[1] * 4) + 25) / 64][(int)(x + 24) / 64] == '1' ||
                           game->map->map[(int)(y + (col[1] * 4) + 25) / 64][(int)(x - 24) / 64] == '1' ||
                           game->map->map[(int)(y + (col[1] * 4) + 25) / 64][(int)(x + 12) / 64] == '1' ||
                           game->map->map[(int)(y + (col[1] * 4) + 25) / 64][(int)(x - 12) / 64] == '1'))
        {
            t = 1;
        }
        if (col[1] < 0 && (game->map->map[(int)(y + (col[1] * 4) - 25) / 64][(int)(x) / 64] == '1' ||
                           game->map->map[(int)(y + (col[1] * 4) - 25) / 64][(int)(x + 24) / 64] == '1' ||
                           game->map->map[(int)(y + (col[1] * 4) - 25) / 64][(int)(x - 24) / 64] == '1' ||
                           game->map->map[(int)(y + (col[1] * 4) - 25) / 64][(int)(x + 12) / 64] == '1' ||
                           game->map->map[(int)(y + (col[1] * 4) - 25) / 64][(int)(x - 12) / 64] == '1'))
        {
            t = 1;
        }
    }

    // Si aucune collision n'est détectée, met à jour la position y du joueur
    if (!t)
        game->player->y_pos += 4 * col[1];
}

void collision_x(t_game *game, float col[2], float x, float y)
{
    int t = 0;

    // Vérifie les quatre coins et les positions adjacentes pour les collisions potentielles en X
    if (game->map->map[(int)(y) / 64][(int)(x + (col[0] * 4)) / 64] != '1' &&
        game->map->map[(int)(y + 24) / 64][(int)(x + (col[0] * 4)) / 64] != '1' &&
        game->map->map[(int)(y - 24) / 64][(int)(x + (col[0] * 4)) / 64] != '1' &&
        game->map->map[(int)(y + 12) / 64][(int)(x + (col[0] * 4)) / 64] != '1' &&
        game->map->map[(int)(y - 12) / 64][(int)(x + (col[0] * 4)) / 64] != '1')
    {
        // Vérifie les collisions potentielles près de la boîte englobante du joueur
        if (col[0] > 0 && (game->map->map[(int)(y) / 64][(int)(x + (col[0] * 4) + 25) / 64] == '1' ||
                           game->map->map[(int)(y + 24) / 64][(int)(x + (col[0] * 4) + 25) / 64] == '1' ||
                           game->map->map[(int)(y - 24) / 64][(int)(x + (col[0] * 4) + 25) / 64] == '1' ||
                           game->map->map[(int)(y + 12) / 64][(int)(x + (col[0] * 4) + 25) / 64] == '1' ||
                           game->map->map[(int)(y - 12) / 64][(int)(x + (col[0] * 4) + 25) / 64] == '1'))
        {
            t = 1;
        }
        else if (col[0] < 0 && (game->map->map[(int)(y) / 64][(int)(x + (col[0] * 4) - 25) / 64] == '1' ||
                                game->map->map[(int)(y + 24) / 64][(int)(x + (col[0] * 4) - 25) / 64] == '1' ||
                                game->map->map[(int)(y - 24) / 64][(int)(x + (col[0] * 4) - 25) / 64] == '1' ||
                                game->map->map[(int)(y + 12) / 64][(int)(x + (col[0] * 4) - 25) / 64] == '1' ||
                                game->map->map[(int)(y - 12) / 64][(int)(x + (col[0] * 4) - 25) / 64] == '1'))
        {
            t = 1;
        }
    }

    // Si aucune collision n'est détectée, met à jour la position x du joueur
    if (!t)
        game->player->x_pos += 4 * col[0];

    // Vérifie les collisions potentielles dans la direction y après avoir mis à jour la position x
    collision_y(game, col, game->player->x_pos, game->player->y_pos);
}

// void	collision_y(t_game *game, float col[2], float x, float y)
// {
// 	int		t;

// 	t = 0;
// 	if (game->map->map[(int)(y + col[1] * 2) / 64][(int)(x) / 64] != '1')
// 	{
// 		if (col[1] > 0 && game->map->map[(int)(y + 25) / 64][(int)(x) / 64] == '1')
// 			t = 1;
// 		if (col[1] < 0 && game->map->map[(int)(y - 25) / 64][(int)(x) / 64] == '1')
// 			t = 1;
// 	}
// 	if (!t)
// 		game->player->y_pos += col[1] * 4;
// }

// void	collision_x(t_game *game, float col[2], float x, float y)
// {
// 	int		t;

// 	t = 0;
// 	if (game->map->map[(int)(y) / 64][(int)(x + col[0] * 2) / 64] != '1')
// 	{
// 		if (col[0] > 0 && game->map->map[(int)(y) / 64][(int)(x + 25) / 64] == '1')
// 			t = 1;
// 		else if (col[0] < 0 && game->map->map[(int)(y) / 64][(int)(x - 25) / 64] == '1')
// 			t = 1;
// 	}
// 	if (!t)
// 		game->player->x_pos += col[0] * 4;
// 	collision_y(game, col, game->player->x_pos, game->player->y_pos);
// }


// void	collision(t_game *game, float col[2], float x, float y)
// {
// 	int		t;

// 	t = 0;
// 	// printf("%d, %d\n", (int)((y / 64) + col[1]), (int)((x / 64) + col[0]));
// 	if (game->map->map[(int)((y / 64) + col[1])][(int)((x / 64) + col[0])] != '1')
// 	{
// 		if (col[0] > 0 && col[1] > 0
// 			&& game->map->map[(int)((y / 64))][(int)((x / 64))] != '1')
// 			t = 1;
// 		else if (col[0] < 0 && col[1] > 0
// 			&& game->map->map[(int)((y / 64))][(int)((x / 64))] != '1')
// 			t = 1;
// 		else if (col[0] > 0 && col[1] < 0
// 			&& game->map->map[(int)((y / 64))][(int)((x / 64))] != '1')
// 			t = 1;
// 		else if (col[0] < 0 && col[1] < 0
// 			&& game->map->map[(int)((y / 64))][(int)((x / 64))] != '1')
// 			t = 1;
// 	}
// 	if (t)
// 	{
// 		game->player->x_pos += 3 * col[0];
// 		game->player->y_pos += 3 * col[1];
// 	}
// }

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
