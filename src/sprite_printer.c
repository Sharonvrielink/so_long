/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_printer.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 13:24:24 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/10 18:49:15 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    load_textimg(mlx_t *mlx, t_sprite *sprite)
{
    /*Space*/
    sprite->space_texture = mlx_load_png("textures/Grass_Texture.png");
    sprite->space_img = mlx_texture_to_image(mlx, sprite->space_texture);
    /*Wall*/
    sprite->wall_texture = mlx_load_png("textures/Hedge.png");
    sprite->wall_img = mlx_texture_to_image(mlx, sprite->wall_texture);
    /*Collectible*/
    sprite->collectible_texture = mlx_load_png("textures/Chick.png");
    sprite->collected_texture = mlx_load_png("textures/Chick_Dead.png");
    sprite->collectible_img = mlx_texture_to_image(mlx, sprite->collectible_texture);
    /*Exit*/
    sprite->exit_texture = mlx_load_png("textures/Flag.png");
    sprite->exit_img = mlx_texture_to_image(mlx, sprite->exit_texture);
    /*Fox*/
    sprite->foxdown_texture = mlx_load_png("textures/Fox_Down.png");
    sprite->fox_img = mlx_texture_to_image(mlx, sprite->foxdown_texture);
    sprite->foxup_texture = mlx_load_png("textures/Fox_Up.png");
    sprite->foxleft_texture = mlx_load_png("textures/Fox_Left.png");
    sprite->foxright_texture = mlx_load_png("textures/Fox_Right.png");
}

void    printsprite(mlx_t *mlx, mlx_image_t *sprite, int32_t x, int32_t y, int32_t depth)
{
    int32_t	id;
    id = mlx_image_to_window(mlx, sprite, x, y);
    mlx_set_instance_depth(&sprite->instances[id], depth);
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
            printsprite(game->mlx, game->sprite.space_img, (x * TILESIZE), (y * TILESIZE), 0);
            if (game->map.grid[y][x] == '1')
                printsprite(game->mlx, game->sprite.wall_img, (x * TILESIZE), (y * TILESIZE), 1);
            if (game->map.grid[y][x] == 'P')
                printsprite(game->mlx, game->sprite.fox_img, (x * TILESIZE), (y * TILESIZE), 2);
            if (game->map.grid[y][x] == 'C')
                printsprite(game->mlx, game->sprite.collectible_img, (x * TILESIZE), (y * TILESIZE), 1);
            if (game->map.grid[y][x] == 'E')
                printsprite(game->mlx, game->sprite.exit_img, (x * TILESIZE), (y * TILESIZE), 1);
            x++;
        }
        y++;
        x = 0;
    }
}
