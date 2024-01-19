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

void ft_putmap(void* param)
{
	t_game *game;

	game = param;

	for (int x = 0; game->map->map[x]; x++)
	{
		for (int y = 0; game->map->map[x][y]; y++)
		{
			if (game->map->map[x][y] == '1')
			{
				uint32_t color = ft_pixel(
					0xFF, // R
					0xAA, // G
					0x00, // B
					0xFF  // A
				);
				spread_pixels(x * 64, y * 64, color);
			}
		}
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	// if (mlx_is_key_down(mlx, MLX_KEY_UP))
	// 	image->instances[0].y -= 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	// 	image->instances[0].y += 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	// 	image->instances[0].x -= 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	// 	image->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

int32_t main(int32_t argc, char* argv[])
{
	mlx_t* mlx;
	t_game	game;

	game.map = malloc (sizeof(t_map));
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
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 1920, 1080)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	ft_putmap(&game);

	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}