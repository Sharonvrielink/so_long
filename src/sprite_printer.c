/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_printer.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 13:24:24 by svrielin      #+#    #+#                 */
/*   Updated: 2022/11/02 15:20:19 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	printsprite(t_game *game, t_mapsprite mapsprite, int32_t x, int32_t y)
{
	int32_t		id;
	int32_t		depth;
	mlx_image_t	*sprite;

	depth = 0;
	if (mapsprite == PLAYER)
	{
		sprite = game->sprite.fox_img;
		depth = 2;
	}
	else if (mapsprite == COLL)
	{
		sprite = game->sprite.chick_img;
		depth = 1;
	}
	else if (mapsprite == EXIT)
	{
		sprite = game->sprite.exit_img;
		depth = 1;
	}
	else
		return ;
	id = mlx_image_to_window(game->mlx, sprite, x, y);
	if (id == -1)
		so_long_error_free(WRONG, game);
	mlx_set_instance_depth(&sprite->instances[id], depth);
}

bool	checkneighbors(char **grid, int32_t x, int32_t y)
{
	if (grid[y + 1][x] != '0')
		return (false);
	else if (grid[y][x + 1] != '0')
		return (false);
	else if (grid[y - 1][x] != '0')
		return (false);
	else if (grid[y][x - 1] != '0')
		return (false);
	else
		return (true);
}

void	printwall(t_game *game, int32_t x, int32_t y)
{
	int32_t		id;
	int32_t		depth;
	mlx_image_t	*sprite;
	bool		check;

	depth = 1;
	check = false;
	if (x > 0 && x < (game->map.columnlen - 1) \
	&& y > 0 && y < (game->map.rowlen - 1))
		check = checkneighbors(game->map.grid, x, y);
	if (check == true)
		sprite = game->sprite.bush_img;
	else
		sprite = game->sprite.wall_img;
	id = mlx_image_to_window(game->mlx, sprite, (x * TILESIZE), (y * TILESIZE));
	if (id == -1)
		so_long_error_free(WRONG, game);
	mlx_set_instance_depth(&sprite->instances[id], depth);
}

void	printspace(t_game *game, int32_t x, int32_t y)
{
	int32_t		id;
	int32_t		depth;
	mlx_image_t	*sprite;

	depth = 0;
	sprite = game->sprite.space_img;
	id = mlx_image_to_window(game->mlx, sprite, x, y);
	if (id == -1)
		so_long_error_free(WRONG, game);
	mlx_set_instance_depth(&sprite->instances[id], depth);
}
