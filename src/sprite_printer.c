/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_printer.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 13:24:24 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/08 19:59:07 by svrielin      ########   odam.nl         */
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

void    printmap(t_gamedata *gamedata)
{
    gamedata->frames = 0;
    gamedata->moves = 0;
    int r = 0;
    //int c = 0;
   // int z;
    char *bermap[] = {
        "1111111111", 
        "1P00000001", 
        "1000000001", 
        "1000000001", 
        "10000000C1", 
        "1000000001", 
        "1000000001", 
        "10C0000001", 
        "10000000E1", 
        "1111111111"};
        
   gamedata->map = (char **)malloc((10 + 1) * sizeof(char *));

    while (r < 10)
    {
        gamedata->map[r] = strdup(bermap[r]);
        r++;
    }

    int x = 0;
    int y = 0;
    while (y < 10)
    {
        while (x < 10)
        {
            printsprite(gamedata->mlx, gamedata->sprite.space_img, (x * TILESIZE), (y * TILESIZE), 0);
            if (gamedata->map[y][x] == '1')
                printsprite(gamedata->mlx, gamedata->sprite.wall_img, (x * TILESIZE), (y * TILESIZE), 1);
            if (gamedata->map[y][x] == 'P')
                printsprite(gamedata->mlx, gamedata->sprite.fox_img, (x * TILESIZE), (y * TILESIZE), 2);
            if (gamedata->map[y][x] == 'C')
                printsprite(gamedata->mlx, gamedata->sprite.collectible_img, (x * TILESIZE), (y * TILESIZE), 1);
            if (gamedata->map[y][x] == 'E')
                printsprite(gamedata->mlx, gamedata->sprite.exit_img, (x * TILESIZE), (y * TILESIZE), 1);
            x++;
        }
        y++;
        x = 0;
    }
}
