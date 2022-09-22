/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 16:44:29 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/22 18:41:36 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <stdio.h> // DON'T FORGET TO REMOVE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include <string.h>
#include <fcntl.h>
#define TILESIZE 64

typedef enum e_mapsprite
{
	SPACE,
	WALL,
	PLAYER,
	COLL,
	EXIT,
} t_mapsprite;

typedef enum e_direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
} t_direction;

typedef enum e_error
{
	SUCCES,
	MAP_WALLS, //map not surrounded by walls
	MAP_CHAR, //unvalid character
	MAP_PLAYER, //map should contain 1 player
	MAP_EXIT, //map should contain 1 exit
	MAP_COLL, //map should contain at least 1 collectible
	MAP_TOOBIG, //map too big for current screen size
}	t_error;

typedef struct s_sprite
{
	mlx_texture_t	*space_texture;
	mlx_texture_t	*wall_texture;
	mlx_texture_t	*rosewall_texture;
	mlx_texture_t	*bush_texture;
	mlx_texture_t	*collectible_texture;
    mlx_texture_t   *collected_texture;
	mlx_texture_t	*exit_texture;
    mlx_texture_t   *foxdown_texture;
    mlx_texture_t   *foxup_texture;
    mlx_texture_t   *foxleft_texture;
    mlx_texture_t   *foxright_texture;
    mlx_image_t     *space_img;
    mlx_image_t     *wall_img;
	mlx_image_t		*rosewall_img;
	mlx_image_t		*bush_img;
    mlx_image_t     *collectible_img;
	mlx_image_t		*collected_img;
    mlx_image_t     *exit_img;
    mlx_image_t     *fox_img;
}   t_sprite;

typedef struct s_check_entity
{
	int	player;
	int	exit;
	int	collectible;
}	t_entity;

typedef struct s_map
{
	char	**grid;
	int		columnlen;
	int 	rowlen;
}	t_map;

typedef struct s_game
{
    mlx_t       *mlx;
    t_map		map;
    t_sprite    sprite;
	int32_t		total_collectibles;
	int32_t		collected;
    int32_t     frames;
    int32_t     moves;
}   t_game;

int32_t 		so_long(const char *map_file);
void			window_init(t_game *game, const char *map_file);
void    		load_textures(t_sprite *sprite);
void			load_images(mlx_t *mlx, t_sprite *sprite);
void    		printsprite(t_game *game, t_mapsprite mapsprite, int32_t x, int32_t y);
void    		printmap(t_game *game);
void			read_map(const char *map_file, t_map *map);
void			move_fox_hook(void *param);
void			move_fox(t_game *game, t_direction direction);
void			get_collectible(t_game *game, mlx_instance_t *collinstance, int32_t x, int32_t y);
void			check_valid_map(t_map *map);
mlx_texture_t	*choose_fox_texture(t_game *game, t_direction direction);
t_mapsprite		check_next_map_position(t_game *game, t_direction direction);
int				so_long_error(t_error errorcode, t_game *game);
void    		delete_img(mlx_t *mlx, t_sprite *sprite);