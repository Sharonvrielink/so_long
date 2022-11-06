/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_printer.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 20:52:37 by svrielin      #+#    #+#                 */
/*   Updated: 2022/11/06 22:20:37 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	check_mapsprite(t_game *game, char c, int x, int y)
{
	int	xpos;
	int	ypos;

	xpos = x * TILESIZE;
	ypos = y * TILESIZE;
	if (c == '1')
		printwall(game, x, y);
	if (c == 'P')
		printsprite(game, PLAYER, xpos, ypos);
	if (c == 'C')
	{
		printsprite(game, COLL, xpos, ypos);
		game->total_collectibles += 1;
	}
	if (c == 'E')
		printsprite(game, EXIT, xpos, ypos);
}

void	printmap(t_game *game)
{
	int	x;
	int	y;

	game->moves = 0;
	game->total_collectibles = 0;
	game->collected = 0;
	x = 0;
	y = 0;
	game->sprite.background = mlx_new_image(game->mlx, game->map.mapwidth, game->map.mapheight);
	mlx_image_to_window(game->mlx, game->sprite.background, 0, 0);
	while (y < (game->map.rowlen))
	{
		while (x < (game->map.columnlen))
		{
			printspace(game, (x * TILESIZE), (y * TILESIZE));
			check_mapsprite(game, game->map.grid[y][x], x, y);
			x++;
		}
		y++;
		x = 0;
	}
}
