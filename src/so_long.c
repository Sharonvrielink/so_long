/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 16:41:54 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/08 11:56:03 by svrielin      ########   odam.nl         */
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
        
    
    // char language[5][10] = {"Java", "Python", "C++", "HTML", "SQL"};

    //printf("%?", *bermap);
   gamedata->map = (char **)malloc((10 + 1) * sizeof(char *));
   printf("sizeof char *: %lu\n", sizeof(char *));
   //namen = malloc(10 * sizeof(char));
   printf("bermap %s\n", *bermap); 
   printf("bermap %s\n", bermap[1]); 
   printf("bermap %c\n", **bermap); 
   printf("bermap %c\n", *(*(bermap + 5)+ 6)); 
	printf("bermap %c\n", bermap[5][6]); 

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

t_mapsprite    check_map_position(t_gamedata *gamedata, t_direction direction)
{
    int32_t xtilepos;
    int32_t ytilepos;
    xtilepos = gamedata->sprite.fox_img->instances[0].x / TILESIZE;
    ytilepos = gamedata->sprite.fox_img->instances[0].y / TILESIZE;
    printf("Previous x pos = %d , y pos = %d\n", xtilepos, ytilepos);//prints the position where the fox is coming from	
    if (direction == UP) 
        ytilepos -= 1;
    if (direction == DOWN)
        ytilepos += 1;
    if (direction == LEFT)
        xtilepos -= 1;
    if (direction == RIGHT)
        xtilepos += 1;
	printf("New x pos = %d , y pos = %d\n", xtilepos, ytilepos);//prints the position where the fox is going to
	if (gamedata->map[ytilepos][xtilepos] == 'C') //d
	{
		printf("COLLECTIBLE\n");
        return(COLLECTIBLE);
	}
    if (gamedata->map[ytilepos][xtilepos] == '1')
        return(WALL);
    else
    	return (SPACE);
}

mlx_texture_t	*choose_fox_texture(t_gamedata *gamedata, t_direction direction)
{
	if (direction == UP)
		return(gamedata->sprite.foxup_texture);
	else if (direction == DOWN)
		return(gamedata->sprite.foxdown_texture);
	else if (direction == LEFT)
		return(gamedata->sprite.foxleft_texture);
	else if (direction == RIGHT)
		return(gamedata->sprite.foxright_texture);
	return (NULL);
}

void	move_fox(t_gamedata *gamedata, t_direction direction)
{
	mlx_texture_t	*texture;
	t_mapsprite		mapsprite;

	mapsprite = check_map_position(gamedata, direction);

	if (mapsprite != WALL)
	{			
		texture = choose_fox_texture(gamedata, direction);
		mlx_draw_texture(gamedata->sprite.fox_img, texture, 0, 0);
		
    	if (direction == UP)
			gamedata->sprite.fox_img->instances[0].y -= TILESIZE;
		if (direction == DOWN)
			gamedata->sprite.fox_img->instances[0].y += TILESIZE;
		if (direction == LEFT)
			gamedata->sprite.fox_img->instances[0].x -= TILESIZE;
		if (direction == RIGHT)
			gamedata->sprite.fox_img->instances[0].x += TILESIZE;	
		gamedata->moves++;
    	printf("Moves: %d\n", gamedata->moves);
	}
	if (mapsprite == COLLECTIBLE)
		mlx_draw_texture(gamedata->sprite.collectible_img, gamedata->sprite.collected_texture, 0, 0);
}

void	move_fox_hook(void *param)
{
	t_gamedata  *gamedata;
    gamedata = param;
    t_mapsprite valid;
	
	valid = SPACE;
    if(gamedata->frames % 6 == 0)
    {
        if (mlx_is_key_down(gamedata->mlx, MLX_KEY_ESCAPE))
            mlx_close_window(gamedata->mlx);
        if (mlx_is_key_down(gamedata->mlx, MLX_KEY_W))
			move_fox(gamedata, UP);
        if (mlx_is_key_down(gamedata->mlx, MLX_KEY_S))
            move_fox(gamedata, DOWN);
        if (mlx_is_key_down(gamedata->mlx, MLX_KEY_A))
            move_fox(gamedata, LEFT);
        if (mlx_is_key_down(gamedata->mlx, MLX_KEY_D))
            move_fox(gamedata, RIGHT);
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
