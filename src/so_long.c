/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 16:41:54 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/09 18:58:48 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//gcc main.c MLX42/libmlx42.a -I include -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

#include "so_long.h"

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
	
	read_map("./maps/smallest_valid.ber");
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
