 #include "cub3d.h"

// static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void spread_pixels(t_game * game, int x, int y, uint32_t color)
{
	int i = 0;
	int j = 0;

	while (i < 16)
	{
		while (j < 16)
		{
			mlx_put_pixel(game->image, x + i, y + j, color);
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
	while (i < 4)
	{
		while (j < 4)
		{
			mlx_put_pixel(game->image, (game->player->x_pos / 4) + i, (game->player->y_pos / 4) + j, 0xFF0000FF);
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

float	dist(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	ft_cast_ray(t_game *game, float ray_length, int ray_pos)
{
	int	i;
	// float	wall_top, wall_bottom;
	float wall_size;

	i = 0;
	(void) game;
	if (ray_pos >= 960)
		return ;
	wall_size = 50000 / ray_length;
	if (wall_size > HEIGHT)
		wall_size = HEIGHT;
	i = HEIGHT / 2 - wall_size / 2;
	// wall_top = -ray_length / 2 + 1000 / 2; //-lineHeight / 2 + 1000 / 2;
	// wall_bottom = ray_length / 2 + 1000 / 2;
	while (i < HEIGHT / 2 + wall_size / 2)
	{
		mlx_put_pixel(game->image, ray_pos, i, game->wall_color);
		i++;
	}
}

float	next_point(t_game *game, float angle, char point)
{
	float	x;
	float	y;

	angle += M_PI / 480;
	x = game->player->x_pos;
	y = game->player->y_pos;
	while (game->map->map[(int)(y / 64)][(int)x / 64] != '1')
	{
		x += cos(angle) * 0.1;
		y += sin(angle) * 0.1;
	}
	if (point == 'x')
		return (x);
	return (y);
}

static void	ft_gendarmes(t_game *game)
{
	// printf("%f\n", fabs(game->ray->last_ray
	// 		- dist(game->player->x_pos, game->player->y_pos, game->ray->x, game->ray->y)
	// 		*cos(game->player->angle - game->ray->angle)));
	if (fabs(game->ray->last_ray
			- (dist(game->player->x_pos, game->player->y_pos, game->ray->x, game->ray->y)
			* cos(game->player->angle - game->ray->angle))) < 50)
	{
		game->ray->jsp = fabs(game->ray->last_x - game->ray->x)
			< fabs(game->ray->last_y - game->ray->y);
	}
	else
	{
		game->ray->jsp = fabs(game->ray->x
				- next_point(game, game->ray->angle, 'x'))
			< fabs(game->ray->y - next_point(game, game->ray->angle, 'y'));
	}
}

void	save(t_game *game)
{
	game->ray->last_ray = dist(game->player->x_pos,
			game->player->y_pos, game->ray->x, game->ray->y)
		*cos(game->player->angle - game->ray->angle);
	game->ray->last_x = game->ray->x;
	game->ray->last_y = game->ray->y;
}

int	choose_texture(t_game *game, float angle)
{
	// printf("%d, %f\n", game->ray->jsp, angle);
	if (!game->ray->jsp)
	{
		if (angle > 0 && angle < M_PI)
			return (0xFF0000FF);
		else
			return (0x00FF00FF);
	}
	else
	{
		if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
			return (0x0000FFFF);
		else
			return (0x00FFFFFF);
	}
	printf("AAAAAAAA\n");
	return (1);
}

void 	put_image(void* param)
{
	t_game *game;
	// int i, j;

	// i = 0;
	// j = 0;
	game = param;
	mlx_delete_image(game->mlx, game->image);
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->ray->angle = game->player->angle - 30 * 0.0174533 - 0.0174533;
	game->ray->length = 0;
	// static float	last_ray;
	int	invisible_ray = 0;
	int		ray_pos = 0;
	int k = 0;
	game->wall_color = 0xFFAA00FF;
	while (ray_pos < WIDTH)
	{
		k = 0;
		game->ray->x = game->player->x_pos;
		game->ray->y = game->player->y_pos;
		if (game->ray->angle < 0)
			game->ray->angle += 2 * M_PI;
		if (game->ray->angle > 2 * M_PI)
			game->ray->angle -= 2 * M_PI;
		while (game->map->map[(int)((game->ray->y / 64) + 0.001)][(int)((game->ray->x / 64) + 0.001)] != '1' && game->map->map[(int)((game->ray->y / 64) - 0.001)][(int)((game->ray->x / 64) - 0.001)] != '1' \
				&& game->map->map[(int)((game->ray->y / 64) - 0.001)][(int)((game->ray->x / 64) + 0.001)] != '1' && game->map->map[(int)((game->ray->y / 64) - 0.001)][(int)((game->ray->x / 64) + 0.001)] != '1')
		{
				// mlx_put_pixel(image, game->ray->x / 4 + 8,
				//  	game->ray->y / 4 + 8, 0x00FFFFFF);
				game->ray->x += cos(game->ray->angle) * 0.1;
				game->ray->y += sin(game->ray->angle) * 0.1;
		}
		game->ray->length = sqrt((game->ray->x - game->player->x_pos) * (game->ray->x - game->player->x_pos) + (game->ray->y - game->player->y_pos) * (game->ray->y - game->player->y_pos));
		game->ray->length *= cos(game->player->angle - game->ray->angle);
		// printf("%f,%f,%f\n", game->player->angle, game->ray->angle ,game->ray->length);
		if (invisible_ray == 1)
		{
			ft_gendarmes(game);
			game->wall_color = choose_texture(game, game->ray->angle);
			while (k < 6 && invisible_ray)
				ft_cast_ray(game, game->ray->length, ray_pos+(k++));
			ray_pos += k;
			// printf("1. %d, %f, %f\n", game->ray->jsp, game->ray->x, game->ray->y);
			// printf("2. %d, %f, %f\n\n", game->ray->jsp, game->ray->x, game->ray->y);
		}
		save(game);
		game->ray->angle += M_PI / 480;
		invisible_ray = 1;
	}
	// for (int x = 0; game->map->map[x]; x++)
	// {
	// 	for (int y = 0; game->map->map[x][y]; y++)
	// 	{
	// 		if (game->map->map[x][y] == '1')
	// 		{
	// 			spread_pixels(game, y * 16, x * 16, 0xFFAA00FF);
	// 		}
	// 	}
	// }
	// i = 0;
	// j = 0;
	// while (i < 4)
	// {
	// 	while (j < 4)
	// 	{
	// 		mlx_put_pixel(image, (game->player->x_pos / 4) + i, (game->player->y_pos / 4) + j, 0xFF0000FF);
	// 		j++;
	// 	}
	// 	i++;
	// 	j = 0;
	// }
	mlx_image_to_window(game->mlx, game->image, 0, 0);
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
			game->player->angle += M_PI / 64;
			if (game->player->angle > 2 * M_PI)
				game->player->angle -= 2 * M_PI;
		}
		if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		{
			// game->player->angle += M_PI_2 / 6;
			// if (game->player->angle > 2 * M_PI)
			// 	game->player->angle = 0;
			game->player->angle -= M_PI / 64;
			if (game->player->angle < 0)
				game->player->angle += 2 * M_PI;
		}
	}
	put_image(game);
}

int main(int argc, char* argv[])
{
	t_game	game;

	game.map = malloc (sizeof(t_map));
	game.player = malloc (sizeof(t_player));
	game.ray = malloc (sizeof(t_ray));
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
	if (!(game.image = mlx_new_image(game.mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game.mlx, game.image, 0, 0) == -1)
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