/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 16:44:29 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/10 17:37:30 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <stdio.h> // DON'T FORGET TO REMOVE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include <string.h>
#include <fcntl.h>
#define WIDTH 640 //for test map 10 x 64
#define HEIGHT 640 //for test map 10 x 64
#define TILESIZE 64

typedef enum e_mapsprite
{
	SPACE,
	WALL,
	COLLECTIBLE,
	EXIT,
} t_mapsprite;

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
    mlx_texture_t   *foxdown_texture;
    mlx_texture_t   *foxup_texture;
    mlx_texture_t   *foxleft_texture;
    mlx_texture_t   *foxright_texture;
    mlx_image_t     *space_img;
    mlx_image_t     *wall_img;
    mlx_image_t     *collectible_img;
    mlx_image_t     *exit_img;
    mlx_image_t     *fox_img;
}   t_sprite;

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
    int32_t     frames;
    int32_t     moves;
}   t_game;

int32_t so_long(void);
void    load_textimg(mlx_t *mlx, t_sprite *sprite);
void    printsprite(mlx_t *mlx, mlx_image_t *sprite, int32_t x, int32_t y, int32_t depth);
void    printmap(t_game *game);
void	read_map(const char *map_file, t_map *map);