/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 16:44:29 by svrielin      #+#    #+#                 */
/*   Updated: 2022/11/10 10:00:48 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include	"MLX42/include/MLX42/MLX42.h"
# include	"libft/libft.h"
# include	<stdlib.h>
# include	<string.h>
# include	<fcntl.h>
# include	<unistd.h>

# define TILESIZE 64

typedef enum e_mapsprite
{
	SPACE,
	WALL,
	PLAYER,
	COLL,
	EXIT,
}	t_mapsprite;

typedef enum e_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
}	t_direction;

typedef enum e_sprite_code
{
	GRASS,
	HEDGE,
	BUSH,
	CHICK,
	CHICK_DEAD,
	FLAG,
	FOX_UP,
	FOX_DOWN,
	FOX_LEFT,
	FOX_RIGHT,
}	t_sprite_code;

typedef enum e_error
{
	SUCCES,
	MAP_EXTENSION,
	MAP_FILE,
	MAP_WALLS,
	MAP_CHAR,
	MAP_PLAYER,
	MAP_EXIT,
	MAP_COLL,
	MAP_PATH,
	MAP_PATH_COLL,
	MAP_TOOBIG,
	MAP_NORECTANGLE,
	WRONG,
	CLOSE,
}	t_error;

typedef struct s_sprite
{
	mlx_texture_t	*texture_array[10];
	mlx_image_t		*background;
	mlx_image_t		*wall_img;
	mlx_image_t		*bush_img;
	mlx_image_t		*chick_img;
	mlx_image_t		*dead_img;
	mlx_image_t		*exit_img;
	mlx_image_t		*fox_img;
}	t_sprite;

typedef struct s_check_entity
{
	int	player;
	int	exit;
	int	collectible;
}	t_entity;

typedef struct s_map
{
	char		**grid;
	int			columnlen;
	int			rowlen;
	int32_t		mapwidth;
	int32_t		mapheight;
	int			startrow;
	int			startcolumn;
	int			total_collectibles;
	t_entity	reached;
}	t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		map;
	t_sprite	sprite;
	int32_t		total_collectibles;
	int32_t		collected;
	int32_t		moves;
}	t_game;

int32_t			so_long(const char *map_file);
const char		*error_messages(t_error errorcode);
void			window_init(t_game *game, const char *map_file);
void			load_textures(t_game *game, t_sprite *sprite);
void			load_images(mlx_t *mlx, t_sprite *sprite);
char			**copy_grid(char **grid, int rowlen);
bool			checkneighbors(char **grid, int32_t x, int32_t y);
void			printwall(t_game *game, int32_t x, int32_t y);
void			printspace(t_game *game, int32_t x, int32_t y);
void			printsprite(t_game *game, t_mapsprite mapsprite, \
				int32_t x, int32_t y);
void			check_mapsprite(t_game *game, char c, int x, int y);
void			printmap(t_game *game);
void			print_lst(t_list *lst);
void			read_map(const char *map_file, t_map *map);
void			move_fox_hook(mlx_key_data_t keydata, void *param);
void			move_fox(t_game *game, t_direction direction);
void			get_collectible(t_game *game, mlx_instance_t *collectible);
void			check_valid_map(t_map *map);
void			check_valid_path(t_map *map);
mlx_texture_t	*choose_fox_texture(t_game *game, t_direction direction);
t_mapsprite		check_next_map_position(t_game *game, t_direction direction);
int				so_long_error_free(t_error code, t_game *game);
int				so_long_error(t_error errorcode, t_map *map);
void			delete_img(mlx_t *mlx, t_sprite *sprite);

#endif