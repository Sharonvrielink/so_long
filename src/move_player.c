/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 14:48:56 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/21 16:13:10 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

t_mapsprite    check_next_map_position(t_game *game, t_direction direction)
{
    int32_t xtilepos;
    int32_t ytilepos;
    xtilepos = game->sprite.fox_img->instances[0].x / TILESIZE;
    ytilepos = game->sprite.fox_img->instances[0].y / TILESIZE;
    if (direction == UP) 
        ytilepos -= 1;
    if (direction == DOWN)
        ytilepos += 1;
    if (direction == LEFT)
        xtilepos -= 1;
    if (direction == RIGHT)
        xtilepos += 1;
	if (game->map.grid[ytilepos][xtilepos] == 'C')
	{
		game->map.grid[ytilepos][xtilepos] = '0';
        return(COLL);
	}
    if (game->map.grid[ytilepos][xtilepos] == '1')
        return(WALL);
	if (game->map.grid[ytilepos][xtilepos] == 'E')
		return(EXIT);
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

void	get_collectible(t_game *game, mlx_instance_t *collinstance, int32_t x, int32_t y)
{
	int i; 
	int32_t id;
	
	i = 0;
	while (i < (game->total_collectibles))
	{
		if (collinstance[i].x == x && collinstance[i].y == y)
		{
			collinstance[i].enabled = false;
			id = mlx_image_to_window(game->mlx, game->sprite.collected_img, x, y);
			mlx_set_instance_depth(&game->sprite.collected_img->instances[id], 1);
			game->collected += 1;
		}
		i++;
	}
}

void	move_fox(t_game *game, t_direction direction)
{
	mlx_texture_t	*texture;
	t_mapsprite		mapsprite;

	mapsprite = check_next_map_position(game, direction);

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
	if (mapsprite == COLL)
	{
		get_collectible(game, game->sprite.collectible_img->instances, game->sprite.fox_img->instances[0].x, game->sprite.fox_img->instances[0].y);
	}
	if (mapsprite == EXIT && game->total_collectibles == game->collected)
		mlx_close_window(game->mlx);
}

void	move_fox_hook(void *param)
{
	t_game  *game;
    game = param;
    if(game->frames % 6 == 0)
    {
        if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
            mlx_close_window(game->mlx);
        else if (mlx_is_key_down(game->mlx, MLX_KEY_W))
			move_fox(game, UP);
        else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
            move_fox(game, DOWN);
        else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
            move_fox(game, LEFT);
        else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
            move_fox(game, RIGHT);
        game->frames = 0;
    }
    game->frames++;
}
