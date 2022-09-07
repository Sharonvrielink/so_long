/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 16:41:54 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/07 17:12:49 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//gcc main.c MLX42/libmlx42.a -I include -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

#include "so_long.h"
//#include "libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define WIDTH 640 //for test map 10 x 64
#define HEIGHT 640 //for test map 10 x 64
#define TILESIZE 64

typedef enum e_direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
} t_direction;

typedef struct s_sprite
{
	mlx_texture_t	*space_texture;
	mlx_texture_t	*wall_texture;
	mlx_texture_t	*collectible_texture;
    mlx_texture_t   *collected_texture;
	mlx_texture_t	*exit_texture;
    mlx_texture_t   *fox_texture;
    mlx_texture_t   *foxup_texture;
    mlx_texture_t   *foxleft_texture;
    mlx_texture_t   *foxright_texture;
    mlx_image_t     *space_img;
    mlx_image_t     *wall_img;
    mlx_image_t     *collectible_img;
    mlx_image_t     *exit_img;
    mlx_image_t     *fox_img;
}   t_sprite;

typedef struct s_gamedata
{
    mlx_t       *mlx;
    char        **map;
    t_sprite    sprite;
    int32_t     frames;
    int32_t     moves;
}   t_gamedata;

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
    sprite->fox_texture = mlx_load_png("textures/Fox_Down.png");
    sprite->fox_img = mlx_texture_to_image(mlx, sprite->fox_texture);
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
    int c = 0;
   // int z;
    char *bermap[] = {
        "1111111111", 
        "1P00000001", 
        "1000000001", 
        "1000000001", 
        "1000000C01", 
        "1000000001", 
        "1000000001", 
        "10C0000001", 
        "10000000E1", 
        "1111111111"};
        
    
    // char language[5][10] = {"Java", "Python", "C++", "HTML", "SQL"};

    //printf("%?", *bermap);
   gamedata->map = (char **)malloc((10 + 1) * sizeof(char *));
   printf("sizeof char *: %lu\n", sizeof(char *));
   //namen = malloc(10 * sizeof(char));
   printf("bermap %s\n", *bermap); 
    while (r < 10)
    {
        while (c < 10)
        {
            gamedata->map[r] = strdup(bermap[r]);
            c++;
        }
        r++;
        c = 0;
    }
    
    printf("gamedata->map[0] %s\n", gamedata->map[0]);
    printf("gamedata->map[1][1] = %c\n", gamedata->map[1][1]);

    int x = 0;
    int y = 0;
    int i = 0;
    int j = 0;
    while (i < 10)
    {
        while (j < 10)
        {
            printsprite(gamedata->mlx, gamedata->sprite.space_img, x, y, 0);
            if (bermap[i][j] == '1')
                printsprite(gamedata->mlx, gamedata->sprite.wall_img, x, y, 1);
            if (bermap[i][j] == 'P')
                printsprite(gamedata->mlx, gamedata->sprite.fox_img, x, y, 2);
            if (bermap[i][j] == 'C')
                printsprite(gamedata->mlx, gamedata->sprite.collectible_img, x, y, 1);
            if (bermap[i][j] == 'E')
                printsprite(gamedata->mlx, gamedata->sprite.exit_img, x, y, 1);
            j++;
            x += TILESIZE;
        }
        i++;
        y += TILESIZE;
        j = 0;
        x = 0;
    }
}

bool    check_valid_position(t_gamedata *gamedata, t_direction direction)
{
    int32_t xtilepos;
    int32_t ytilepos;
    xtilepos = gamedata->sprite.fox_img->instances[0].x / TILESIZE;
    ytilepos = gamedata->sprite.fox_img->instances[0].y / TILESIZE;
    printf("x pos = %d , y pos = %d\n", xtilepos, ytilepos);
    if (direction == UP) 
        ytilepos -= 1;
    if (direction == DOWN)
        ytilepos += 1;
    if (direction == LEFT)
        xtilepos -= 1;
    if (direction == RIGHT)
        xtilepos += 1;
    if (gamedata->map[xtilepos][ytilepos] == 'C')//location does not work and all textures change
        mlx_draw_texture(gamedata->sprite.collectible_img, gamedata->sprite.collected_texture, 0, 0);
    if (gamedata->map[xtilepos][ytilepos] == '1')
        return(false);
    else
        return (true);
}

void	move_fox_hook(void *param)
{
	t_gamedata  *gamedata;
    gamedata = param;
    bool valid;

    valid = true;
    if(gamedata->frames % 6 == 0)
    {
        if (mlx_is_key_down(gamedata->mlx, MLX_KEY_ESCAPE))
            mlx_close_window(gamedata->mlx);
        if (mlx_is_key_down(gamedata->mlx, MLX_KEY_UP))
        {
            valid = check_valid_position(gamedata, UP);
            if (valid == true)
            {
                mlx_draw_texture(gamedata->sprite.fox_img, gamedata->sprite.foxup_texture, 0, 0);
                gamedata->sprite.fox_img->instances[0].y -= TILESIZE;
                //printf("up\n");
                gamedata->moves++;
                printf("Moves: %d\n", gamedata->moves);
            }
        }
        if (mlx_is_key_down(gamedata->mlx, MLX_KEY_DOWN))
        {
            valid = check_valid_position(gamedata, DOWN);
            if (valid == true)
            {
                mlx_draw_texture(gamedata->sprite.fox_img, gamedata->sprite.fox_texture, 0, 0);
                gamedata->sprite.fox_img->instances[0].y += TILESIZE;
                //printf("down\n");
                gamedata->moves++;
                printf("Moves: %d\n", gamedata->moves);
            }
        }
        if (mlx_is_key_down(gamedata->mlx, MLX_KEY_LEFT))
        {
            valid = check_valid_position(gamedata, LEFT);
            if (valid == true)
            {
                mlx_draw_texture(gamedata->sprite.fox_img, gamedata->sprite.foxleft_texture, 0, 0);
                gamedata->sprite.fox_img->instances[0].x -= TILESIZE;
                //printf("left\n");
                gamedata->moves++;
                printf("Moves: %d\n", gamedata->moves);
            }
        }
        if (mlx_is_key_down(gamedata->mlx, MLX_KEY_RIGHT))
        {
            valid = check_valid_position(gamedata, RIGHT);
            if (valid == true)
            {
                mlx_draw_texture(gamedata->sprite.fox_img, gamedata->sprite.foxright_texture, 0, 0);
                gamedata->sprite.fox_img->instances[0].x += TILESIZE;
                //printf("right\n");
                gamedata->moves++;
                printf("Moves: %d\n", gamedata->moves);
            }
        }
        gamedata->frames = 0;
    }
    gamedata->frames++;
}


void    delete_img(mlx_t *mlx, t_sprite *sprite)
{
    mlx_delete_image(mlx, sprite->space_img); //Cleanup the image after exit
    mlx_delete_image(mlx, sprite->wall_img);
    mlx_delete_image(mlx, sprite->collectible_img);
    mlx_delete_image(mlx, sprite->exit_img);
    mlx_delete_image(mlx, sprite->fox_img);
}

int32_t so_long(void)
{
    t_gamedata gamedata;

    gamedata.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
    if (!gamedata.mlx)
        exit(EXIT_FAILURE); //These exit statuses are defined in stdlib, failure is 1 success = 0 
    load_textimg(gamedata.mlx, &gamedata.sprite);
    printmap(&gamedata);
    mlx_loop_hook(gamedata.mlx, &move_fox_hook, &gamedata);
    mlx_loop(gamedata.mlx); //Rendering of mlx, which loops until the window is closed
    delete_img(gamedata.mlx, &gamedata.sprite);
	mlx_terminate(gamedata.mlx);
	return (EXIT_SUCCESS);
}
