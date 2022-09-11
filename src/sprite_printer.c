/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_printer.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 13:24:24 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/11 19:49:52 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_textimg(mlx_t *mlx, t_sprite *sprite)
{
	sprite->space_texture = mlx_load_png("textures/Grass_Texture.png");
	sprite->space_img = mlx_texture_to_image(mlx, sprite->space_texture);
	sprite->wall_texture = mlx_load_png("textures/Hedge.png");
	sprite->wall_img = mlx_texture_to_image(mlx, sprite->wall_texture);
	sprite->rosewall_texture = mlx_load_png("textures/Hedge_Roses.png");
	sprite->rosewall_img = mlx_texture_to_image(mlx, sprite->rosewall_texture);
	sprite->bush_texture = mlx_load_png("textures/Bush.png");
	sprite->bush_img = mlx_texture_to_image(mlx, sprite->bush_texture);
	sprite->collectible_texture = mlx_load_png("textures/Chick.png");
	sprite->collected_texture = mlx_load_png("textures/Chick_Dead.png");
	sprite->collectible_img = mlx_texture_to_image(mlx, sprite->collectible_texture);
	sprite->exit_texture = mlx_load_png("textures/Flag.png");
	sprite->exit_img = mlx_texture_to_image(mlx, sprite->exit_texture);
	sprite->foxdown_texture = mlx_load_png("textures/Fox_Down.png");
	sprite->fox_img = mlx_texture_to_image(mlx, sprite->foxdown_texture);
	sprite->foxup_texture = mlx_load_png("textures/Fox_Up.png");
	sprite->foxleft_texture = mlx_load_png("textures/Fox_Left.png");
	sprite->foxright_texture = mlx_load_png("textures/Fox_Right.png");
}

void	printsprite(t_game *game, t_mapsprite mapsprite, int32_t x, int32_t y)
{
    int32_t		id;
	int32_t		depth;
	mlx_image_t	*sprite;
	
	depth = 0;
	// if (mapsprite == WALL)
	// {
	// 	sprite = game->sprite.wall_img;
	// 	depth = 1;
	// }
	if (mapsprite == PLAYER)
	{
		sprite = game->sprite.fox_img;
		depth = 2;
	}
	else if (mapsprite == COLL)
	{
		sprite = game->sprite.collectible_img;
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
    mlx_set_instance_depth(&sprite->instances[id], depth);
}

bool	checkneighbors(char **grid, int32_t x, int32_t y)
{
	//check down
    if (grid[y + 1][x] != '0')
        return false;
    //check right
    else if (grid[y][x + 1] != '0')
    	return false;
    //check up
    else if (grid[y - 1][x] != '0')
        return false;
    //check left
    else if (grid[y][x - 1] != '0')
        return false;
	else
		return true;
}

void	printwall(t_game *game, int32_t x, int32_t y)
{
	int32_t		id;
	int32_t		depth;
	mlx_image_t	*sprite;
	bool		check;

	depth = 1;
	check = false;
	if (x > 0 && x < (game->map.columnlen - 1) && y > 0 && y < (game->map.rowlen - 1))
		check = checkneighbors(game->map.grid, x, y);
	if (check == true)
		sprite = game->sprite.bush_img;
	else
		sprite = game->sprite.wall_img;
	id = mlx_image_to_window(game->mlx, sprite, (x * TILESIZE), (y * TILESIZE));
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
    mlx_set_instance_depth(&sprite->instances[id], depth);
}

void	check_mapsprite(t_game *game, char c, int x, int y)
{
	int xpos;
	int ypos;

	xpos = x * TILESIZE;
	ypos = y * TILESIZE;
    if (c == '1')
        printwall(game, x, y);
    if (c == 'P')
        printsprite(game, PLAYER, xpos, ypos);
    if (c == 'C')
        printsprite(game, COLL, xpos, ypos);
    if (c == 'E')
        printsprite(game, EXIT, xpos, ypos);
}

void    printmap(t_game *game)
{
    game->frames = 0;
    game->moves = 0;

    int x = 0;
    int y = 0;
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
