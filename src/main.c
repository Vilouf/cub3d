 #include "cub3d.h"

double	dist(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int	choose_texture(t_game *game, float angle)
{
	if (!game->ray->jsp)
	{
		if (angle > 0 && angle < M_PI)
			game->current_txt = game->s_txt;
		else
			game->current_txt = game->n_txt;
	}
	else
	{
		if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
			game->current_txt = game->w_txt;
		else
			game->current_txt = game->e_txt;
	}
	return (1);
}

void 	put_image(void* param)
{
	t_game *game;

	game = param;
	mlx_delete_image(game->mlx, game->image);
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->ray->angle = game->player->angle - 30 * 0.0174533 - 0.0174533;
	game->ray->length = 0;
	int	invisible_ray = 0;
	int		ray_pos = 0;
	int k = 0;
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
				game->ray->x += cos(game->ray->angle) * 0.1;
				game->ray->y += sin(game->ray->angle) * 0.1;
		}
		game->ray->length = dist(game->player->x_pos, game->player->y_pos, game->ray->x, game->ray->y);
		game->ray->length *= cos(game->player->angle - game->ray->angle);
		if (invisible_ray == 1)
		{
			ft_gendarmes(game);
			game->wall_color = choose_texture(game, game->ray->angle);
			while (k < 6 && invisible_ray)
				ft_cast_ray(game, game->ray->length, ray_pos+(k++));
			ray_pos += k;
		}
		save(game);
		game->ray->angle += M_PI / 480;
		invisible_ray = 1;
	}
	mlx_image_to_window(game->mlx, game->image, 0, 0);
}



// int main(int argc, char* argv[])
// {
// 	t_game	game;

// 	game.map = malloc (sizeof(t_map));
// 	game.player = malloc (sizeof(t_player));
// 	game.ray = malloc (sizeof(t_ray));
// 	game.argv = argv;
// 	game.argc = argc;
// 	game.map->x = 0;
// 	game.map->y = 0;
// 	game.map->x_size = 0;
// 	game.map->y_size = 0;
// 	ft_load_png(&game);

// 	map(&game);

// 	for (int i = 0; game.map->map[i]; i++)
// 	{
// 		for (int j = 0; game.map->map[i][j]; j++)
// 		{
// 			printf("%c", game.map->map[i][j]);
// 		}
// 		printf("\n");
// 	}

// 	// Gotta error check this stuff
// 	if (!(game.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
// 	{
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (!(game.image = mlx_new_image(game.mlx, WIDTH, HEIGHT)))
// 	{
// 		mlx_close_window(game.mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (mlx_image_to_window(game.mlx, game.image, 0, 0) == -1)
// 	{
// 		mlx_close_window(game.mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}

// 	ft_init_map(&game);

// 	mlx_loop_hook(game.mlx, ft_hook, &game);
// 	mlx_loop(game.mlx);
// 	mlx_terminate(game.mlx);
// 	return (EXIT_SUCCESS);
// }

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
	free(game.map->path_n);
	free(game.map->path_s);
	free(game.map->path_e);
	free(game.map->path_w);
	freetab(game.map->map);
	free(game.map);
	free(game.player);
	return (EXIT_SUCCESS);
}
