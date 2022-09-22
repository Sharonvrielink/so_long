/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 16:41:54 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/22 10:06:31 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//gcc main.c MLX42/libmlx42.a -I include -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

#include "so_long.h"

void    delete_img(mlx_t *mlx, t_sprite *sprite)
{
    mlx_delete_image(mlx, sprite->space_img); //Cleanup the image after exit
    mlx_delete_image(mlx, sprite->wall_img);
	mlx_delete_image(mlx, sprite->bush_img);
    mlx_delete_image(mlx, sprite->collectible_img);
    mlx_delete_image(mlx, sprite->exit_img);
    mlx_delete_image(mlx, sprite->fox_img);
}

void	window_init(t_game *game, const char *map_file)
{
	int32_t	mapwidth;
	int32_t	mapheight;
	int32_t	screenwidth;
	int32_t	screenheight;
	
	read_map(map_file, &game->map);
	mapwidth = game->map.columnlen * TILESIZE;
	mapheight = game->map.rowlen * TILESIZE;
	game->mlx = mlx_init(mapwidth, mapheight, "MLX42", true);
	if (!game->mlx)
        exit(EXIT_FAILURE); //These exit statuses are defined in stdlib, failure is 1 success = 0 
	mlx_get_monitor_size(0, &screenwidth, &screenheight);
	printf("screenwidth = %d, screenheight %d\n", screenwidth, screenheight);
	if (screenwidth < mapwidth || screenheight < mapheight)
	{
		printf("too big!\n");
		delete_img(game->mlx, &game->sprite);
		mlx_terminate(game->mlx);
		exit(EXIT_FAILURE);
	}
}

int32_t so_long(const char *map_file)
{
    t_game	game;
	window_init(&game, map_file);
    load_textures(&game.sprite);
	load_images(game.mlx, &game.sprite);
    printmap(&game);
    mlx_loop_hook(game.mlx, &move_fox_hook, &game);
    mlx_loop(game.mlx); //Rendering of mlx, which loops until the window is closed
    delete_img(game.mlx, &game.sprite);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
