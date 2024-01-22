 #include "cub3d.h"

static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void spread_pixels(int x, int y, uint32_t color)
{
	int i = 0;
	int j = 0;

	while (i < 64)
	{
		while (j < 64)
		{
			mlx_put_pixel(image, x + i, y + j, color);
			j++;
		}
		i++;
		j = 0;
	}
}

void	init_player_pos(t_game *game)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 16)
	{
		while (j < 16)
		{
			mlx_put_pixel(image, game->player->x_pos + i, game->player->y_pos + j, 0xFF0000FF);
			j++;
		}
		i++;
		j = 0;
	}
}

void ft_init_map(void* param)
{
	t_game *game;

	game = param;

	for (int x = 0; game->map->map[x]; x++)
	{
		for (int y = 0; game->map->map[x][y]; y++)
		{
			if (game->map->map[x][y] == '1')
			{
				spread_pixels(y * 64, x * 64, 0xFFAA00FF);
			}
			else if (game->map->map[x][y] == 'E')
			{
				game->player->x_pos = (y * 64) + 24;
				game->player->y_pos = (x * 64) + 24;
				game->player->angle = 0;
				init_player_pos(game);
			}
		}
	}
}

int	collision(t_game *game, double x_pos, double y_pos)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->y_size)
	{
		x = 0;
		while (game->map->map[y][x])
		{
			if (game->map->map[y][x] == '1')
			{
				if (y_pos <= (double) y * 64 + 64 \
					&& y_pos >= (double) y * 64 \
					&& x_pos <= (double) x * 64 + 64 \
					&& x_pos >= (double) x * 64)
				{
					return (0);
				}
			}
			x++;
		}
		y++;
	}
	return (1);
}

void put_image(void* param)
{
	t_game *game;
	int i, j;

	i = 0;
	j = 0;
	game = param;
	mlx_delete_image(game->mlx, image);
	image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	for (int x = 0; game->map->map[x]; x++)
	{
		for (int y = 0; game->map->map[x][y]; y++)
		{
			if (game->map->map[x][y] == '1')
			{
				spread_pixels(y * 64, x * 64, 0xFFAA00FF);
			}
		}
	}
	while (i < 16)
	{
		while (j < 16)
		{
			mlx_put_pixel(image, game->player->x_pos + i, game->player->y_pos + j, 0xFF0000FF);
			j++;
		}
		i++;
		j = 0;
	}
	double	ray_angle = M_PI / 3 * -1;
	while (ray_angle < M_PI / 3)
	{
		i = 0;
		j = 0;
		while (i < 2000)
		{
			if (collision(game, (game->player->x_pos + i * cos(game->player->angle + ray_angle)) + 8, (game->player->y_pos + j * sin(game->player->angle + ray_angle)) + 8))
			{
				mlx_put_pixel(image, (game->player->x_pos + i * cos(game->player->angle + ray_angle)) + 8, \
					(game->player->y_pos + j * sin(game->player->angle + ray_angle)) + 8, 0x00FFFFFF);
			}
			else
				break ;
			i++;
			j++;
		}
		ray_angle += M_PI / 240;
	}
	mlx_image_to_window(game->mlx, image, 0, 0);
}

int	ft_movement(mlx_t *mlx)
{
	return(mlx_is_key_down(mlx, MLX_KEY_W) 
		|| mlx_is_key_down(mlx, MLX_KEY_S)
		|| mlx_is_key_down(mlx, MLX_KEY_A)
		|| mlx_is_key_down(mlx, MLX_KEY_D)
		|| mlx_is_key_down(mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(mlx, MLX_KEY_LEFT));
}

void	ft_hook(void* param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (ft_movement(game->mlx))
	{
		if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		{
			game->player->x_pos -= 2 * -cos(game->player->angle);
			game->player->y_pos -= 2 * -sin(game->player->angle);
		}
		if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		{
			game->player->x_pos += 2 * -cos(game->player->angle);
			game->player->y_pos += 2 * -sin(game->player->angle);
		}
		if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		{
			game->player->x_pos -= 2 * -sin(game->player->angle);
			game->player->y_pos -= 2 * cos(game->player->angle);
		}
		if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		{
			game->player->x_pos += 2 * -sin(game->player->angle);
			game->player->y_pos += 2 * cos(game->player->angle);
		}
		if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		{
			// game->player->angle -= M_PI_2 / 16;
			// if (game->player->angle < 0)
			// 	game->player->angle = 2 * M_PI;
			game->player->angle += M_PI_2 / 32;
			if (game->player->angle > 2 * M_PI)
				game->player->angle = 0;
		}
		if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		{
			// game->player->angle += M_PI_2 / 6;
			// if (game->player->angle > 2 * M_PI)
			// 	game->player->angle = 0;
			game->player->angle -= M_PI_2 / 32;
			if (game->player->angle < 0)
				game->player->angle = 2 * M_PI;
		}
		put_image(game);
	}
}

int main(int argc, char* argv[])
{
	t_game	game;

	game.map = malloc (sizeof(t_map));
	game.player = malloc (sizeof(t_player));
	game.argv = argv;
	game.argc = argc;
	game.map->x = 0;
	game.map->y = 0;
	game.map->x_size = 0;
	game.map->y_size = 0;

	map(&game);

	for (int i = 0; game.map->map[i]; i++)
	{
		for (int j = 0; game.map->map[i][j]; j++)
		{
			printf("%c", game.map->map[i][j]);
		}
		printf("\n");
	}

	// Gotta error check this stuff
	if (!(game.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(game.mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game.mlx, image, 0, 0) == -1)
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	ft_init_map(&game);

	mlx_loop_hook(game.mlx, ft_hook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}