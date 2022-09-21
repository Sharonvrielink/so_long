/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 16:41:54 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/21 17:17:11 by svrielin      ########   odam.nl         */
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

void	window_init(t_game *game)
{
	int32_t	width;
	int32_t	height;
	int32_t	screenwidth;
	int32_t	screenheight;
	
	read_map("./maps/medium_34x6tiles.ber", &game->map);
	width = game->map.columnlen * TILESIZE;
	height = game->map.rowlen * TILESIZE;
	printf("width = %d, height %d\n", width, height);
	game->mlx = mlx_init(width, height, "MLX42", true);
	if (!game->mlx)
        exit(EXIT_FAILURE); //These exit statuses are defined in stdlib, failure is 1 success = 0 
	mlx_get_monitor_size(0, &screenwidth, &screenheight);
	printf("screenwidth = %d, screenheight %d\n", screenwidth, screenheight);
	if (screenwidth < width || screenheight < height)
	{
		printf("too big!\n");
		delete_img(game->mlx, &game->sprite);
		mlx_terminate(game->mlx);
		exit(EXIT_FAILURE);
	}
}

int32_t so_long(void)
{
    t_game	game;
	window_init(&game);
    load_textures(&game.sprite);
	load_images(game.mlx, &game.sprite);
    printmap(&game);
    mlx_loop_hook(game.mlx, &move_fox_hook, &game);
    mlx_loop(game.mlx); //Rendering of mlx, which loops until the window is closed
    delete_img(game.mlx, &game.sprite);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
