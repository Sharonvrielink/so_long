/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 14:48:56 by svrielin      #+#    #+#                 */
/*   Updated: 2022/11/10 12:29:59 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

t_mapsprite	check_next_map_position(t_game *game, t_direction direction)
{
	int32_t	xtilepos;
	int32_t	ytilepos;

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
		return (COLL);
	}
	if (game->map.grid[ytilepos][xtilepos] == '1')
		return (WALL);
	if (game->map.grid[ytilepos][xtilepos] == 'E')
		return (EXIT);
	else
		return (SPACE);
}

mlx_texture_t	*choose_fox_texture(t_game *game, t_direction direction)
{
	if (direction == UP)
		return (game->sprite.texture_array[FOX_UP]);
	else if (direction == DOWN)
		return (game->sprite.texture_array[FOX_DOWN]);
	else if (direction == LEFT)
		return (game->sprite.texture_array[FOX_LEFT]);
	else if (direction == RIGHT)
		return (game->sprite.texture_array[FOX_RIGHT]);
	return (NULL);
}

void	get_collectible(t_game *game, mlx_instance_t *collectible)
{
	int		i;
	int32_t	x;
	int32_t	y;
	int32_t	id;

	i = 0;
	x = game->sprite.fox_img->instances[0].x;
	y = game->sprite.fox_img->instances[0].y;
	while (i < (game->total_collectibles))
	{
		if (collectible[i].x == x && collectible[i].y == y)
		{
			collectible[i].enabled = false;
			id = mlx_image_to_window(game->mlx, game->sprite.dead_img, x, y);
			if (id == -1)
				so_long_error_free(WRONG, game);
			mlx_set_instance_depth(&game->sprite.dead_img->instances[id], 1);
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
		if (mlx_draw_texture(game->sprite.fox_img, texture, 0, 0))
		{
			if (direction == UP)
				game->sprite.fox_img->instances[0].y -= TILESIZE;
			if (direction == DOWN)
				game->sprite.fox_img->instances[0].y += TILESIZE;
			if (direction == LEFT)
				game->sprite.fox_img->instances[0].x -= TILESIZE;
			if (direction == RIGHT)
				game->sprite.fox_img->instances[0].x += TILESIZE;
			game->moves++;
			ft_printf("Moves: %d\n", game->moves);
		}
	}
	if (mapsprite == COLL)
		get_collectible(game, game->sprite.chick_img->instances);
	if (mapsprite == EXIT && game->total_collectibles == game->collected)
		so_long_error_free(SUCCES, game);
}

void	move_fox_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || \
	keydata.action == MLX_REPEAT))
		move_fox(game, UP);
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || \
	keydata.action == MLX_REPEAT))
		move_fox(game, DOWN);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || \
	keydata.action == MLX_REPEAT))
		move_fox(game, LEFT);
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || \
	keydata.action == MLX_REPEAT))
		move_fox(game, RIGHT);
}
