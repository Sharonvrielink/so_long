/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 16:41:54 by svrielin      #+#    #+#                 */
/*   Updated: 2022/11/06 16:56:32 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	delete_img(mlx_t *mlx, t_sprite *sprite)
{
	mlx_delete_image(mlx, sprite->background);
	mlx_delete_image(mlx, sprite->wall_img);
	mlx_delete_image(mlx, sprite->bush_img);
	mlx_delete_image(mlx, sprite->chick_img);
	mlx_delete_image(mlx, sprite->dead_img);
	mlx_delete_image(mlx, sprite->exit_img);
	mlx_delete_image(mlx, sprite->fox_img);
}

void	window_init(t_game *game, const char *map_file)
{
	int32_t	screenwidth;
	int32_t	screenheight;

	read_map(map_file, &game->map);
	game->map.mapwidth = game->map.columnlen * TILESIZE;
	game->map.mapheight = game->map.rowlen * TILESIZE;
	game->mlx = mlx_init(game->map.mapwidth, game->map.mapheight, "so_long", true);
	if (!game->mlx)
		exit(EXIT_FAILURE);
	mlx_get_monitor_size(0, &screenwidth, &screenheight);
	if (screenwidth < game->map.mapwidth || screenheight < game->map.mapheight)
		so_long_error_free(MAP_TOOBIG, game);
}

int32_t	so_long(const char *map_file)
{
	t_game	game;
	size_t	len;

	len = ft_strlen(map_file);
	if (ft_strncmp(map_file + len - 4, ".ber", 4))
		so_long_error(MAP_EXTENSION, NULL);
	window_init(&game, map_file);
	load_textures(&game, &game.sprite);
	load_images(game.mlx, &game.sprite);
	printmap(&game);
	mlx_key_hook(game.mlx, &move_fox_hook, &game);
	mlx_loop(game.mlx);
	return (so_long_error_free(CLOSE, &game));
}
