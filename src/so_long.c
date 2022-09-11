/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 16:41:54 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/11 14:15:36 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//gcc main.c MLX42/libmlx42.a -I include -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

#include "so_long.h"

t_mapsprite    check_map_position(t_game *game, t_direction direction)
{
    int32_t xtilepos;
    int32_t ytilepos;
    xtilepos = game->sprite.fox_img->instances[0].x / TILESIZE;
    ytilepos = game->sprite.fox_img->instances[0].y / TILESIZE;
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
	if (game->map.grid[ytilepos][xtilepos] == 'C') //d
	{
		printf("COLLECTIBLE\n");
        return(COLLECTIBLE);
	}
    if (game->map.grid[ytilepos][xtilepos] == '1')
        return(WALL);
    else
    	return (SPACE);
}

mlx_texture_t	*choose_fox_texture(t_game *game, t_direction direction)
{
	if (direction == UP)
		return(game->sprite.foxup_texture);
	else if (direction == DOWN)
		return(game->sprite.foxdown_texture);
	else if (direction == LEFT)
		return(game->sprite.foxleft_texture);
	else if (direction == RIGHT)
		return(game->sprite.foxright_texture);
	return (NULL);
}

void	move_fox(t_game *game, t_direction direction)
{
	mlx_texture_t	*texture;
	t_mapsprite		mapsprite;

	mapsprite = check_map_position(game, direction);

	if (mapsprite != WALL)
	{			
		texture = choose_fox_texture(game, direction);
		mlx_draw_texture(game->sprite.fox_img, texture, 0, 0);
		
    	if (direction == UP)
			game->sprite.fox_img->instances[0].y -= TILESIZE;
		if (direction == DOWN)
			game->sprite.fox_img->instances[0].y += TILESIZE;
		if (direction == LEFT)
			game->sprite.fox_img->instances[0].x -= TILESIZE;
		if (direction == RIGHT)
			game->sprite.fox_img->instances[0].x += TILESIZE;	
		game->moves++;
    	printf("Moves: %d\n", game->moves);
	}
	if (mapsprite == COLLECTIBLE)
		mlx_draw_texture(game->sprite.collectible_img, game->sprite.collected_texture, 0, 0);
}

void	move_fox_hook(void *param)
{
	t_game  *game;
    game = param;
    if(game->frames % 6 == 0)
    {
        if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
            mlx_close_window(game->mlx);
        if (mlx_is_key_down(game->mlx, MLX_KEY_W))
			move_fox(game, UP);
        if (mlx_is_key_down(game->mlx, MLX_KEY_S))
            move_fox(game, DOWN);
        if (mlx_is_key_down(game->mlx, MLX_KEY_A))
            move_fox(game, LEFT);
        if (mlx_is_key_down(game->mlx, MLX_KEY_D))
            move_fox(game, RIGHT);
        game->frames = 0;
    }
    game->frames++;
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
    t_game	game;
	int32_t	width;
	int32_t	height;
	
	width = 0;
	height = 0;
	mlx_get_monitor_size(0, &width, &height);
	printf("screenwidth = %d, screenheight %d\n", width, height);
	read_map("./maps/toobig.ber", &game.map);
	width = game.map.columnlen * TILESIZE; //40 tiles
	height = game.map.rowlen * TILESIZE;
    game.mlx = mlx_init(width, height, "MLX42", true);
    if (!game.mlx)
        exit(EXIT_FAILURE); //These exit statuses are defined in stdlib, failure is 1 success = 0 
    load_textimg(game.mlx, &game.sprite);
    printmap(&game);
    mlx_loop_hook(game.mlx, &move_fox_hook, &game);
    mlx_loop(game.mlx); //Rendering of mlx, which loops until the window is closed
    delete_img(game.mlx, &game.sprite);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
