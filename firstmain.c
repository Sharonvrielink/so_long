/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 10:33:09 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/01 13:08:36 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//gcc main.c MLX42/libmlx42.a -I include -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#define WIDTH 640 //for test map 10 x 64
#define HEIGHT 640 //for test map 10 x 64

typedef struct s_maptextures
{
	mlx_texture_t	*space_texture;
	mlx_texture_t	*wall_texture;
	mlx_texture_t	*collectible_texture;
	mlx_texture_t	*exit_texture;
}	t_maptextures;

typedef struct s_mapimg
{
    mlx_image_t     *space_img;
    mlx_image_t     *wall_img;
    mlx_image_t     *collectible_img;
    mlx_image_t     *exit_img;
}   t_mapimg;

// void	load_map_textimg(mlx_t *mlx, t_map *map)
// {   
//     printf("within load_map_textimg\n");
// 	/*space*/
//     map->space_texture = mlx_load_png("textures/Grass_Texture.png");
//     printf("after mlx_load_png\n");
//     map->space_img = mlx_new_image(mlx, 64, 64);
//     printf("after new image\n");
//     map->space_img = mlx_texture_to_image(mlx, map->space_texture);
//     printf("after texture to image\n");
//     /*wall*/
// 	map->wall_texture = mlx_load_png("textures/Hedge.png");
//     map->wall_img = mlx_new_image(mlx, 64, 64);
//     map->wall_img = mlx_texture_to_image(mlx, map->wall_texture);
//     /*collectible*/
//     map->collectible_texture = mlx_load_png("textures/Chick.png");
//     map->collectible_img = mlx_new_image(mlx, 64, 64);
//     map->collectible_img = mlx_texture_to_image(mlx, map->collectible_texture);
//     /*exit*/ 
// }

// void    print_map(mlx_t *mlx, t_map *map)
// {
//     printf("!\n");
//     mlx_image_to_window(mlx, map->collectible_img, 0, 0);
    
// }

void    delete_img(t_mapimg *mapimgs, mlx_t *mlx)
{
    mlx_delete_image(mlx, mapimgs->space_img); //Cleanup the image after exit
    //mlx_delete_image(mlx, map->wall_img);
}

int32_t main(void)
{
    mlx_t   *mlx;
    t_maptextures   *maptextures;
    t_mapimg        *mapimgs;
    // mlx_texture_t   *spacetexture;
    // mlx_image_t     *spaceimg;
    mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
    if (!mlx)
        exit(EXIT_FAILURE); //These exit statuses are defined in stdlib, failure is 1 success = 0 
    //load_map_textimg(mlx, map);
    maptextures->space_texture = mlx_load_png("textures/Grass_Texture.png");
    printf("after mlx_load_png\n");
    mapimgs->space_img = mlx_new_image(mlx, 64, 64);
    printf("after mlx_newimage\n");
    mapimgs->space_img = mlx_texture_to_image(mlx, maptextures->space_texture);
    printf("after texture to image\n");
    mlx_image_to_window(mlx, mapimgs->space_img, 0, 0);
    printf("Outside load_map_textimg\n");
    mlx_loop(mlx); //Rendering of mlx, which loops until the window is closed
	delete_img(mapimgs, mlx); //Cleanup images after exit
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

    //print_map(mlx, map);
    // char bermap[10][10] = {
    //     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    // };

    // int x = 0;
    // int y = 0;
    // int i = 0;
    // int j = 0;
    // int32_t	id;
    // printf("Within print_map function\n");
    // while (i < 10)
    // {
    //     //if (bermap[i][j] == 0)
    //     mlx_image_to_window(mlx, map->space_img, x, y);
    //     if (bermap[i][j] == 1)
    //     {
    //         printf("hedge\n");
    //         id = mlx_image_to_window(mlx, map->wall_img, x, y);
    //         mlx_set_instance_depth(&map->wall_img->instances[id], 1);
    //     }
    //     // if (bermap[i][j] == 'P')
    //     // {
    //     //     printf("player\n");
    //     //     id = mlx_image_to_window(mlx, fox_img, x, y);
    //     //     mlx_set_instance_depth(&fox_img->instances[id], 1);
    //     // }
    //     while (j < 10)
    //     {
    //         //if (bermap[i][j] == 0)
    //             mlx_image_to_window(mlx, map->space_img, x, y);
    //         if (bermap[i][j] == 1)
    //         {
    //             mlx_image_to_window(mlx, map->wall_img, x, y);
    //             //mlx_set_instance_depth(&hedge_img->instances[id], 1); z is al 1 (bepaald door eerste set_instance)
    //         }
    //         // if (bermap[i][j] == 'P')
    //         // {
    //         //     id = mlx_image_to_window(mlx, fox_img, x, y);
    //         //     mlx_set_instance_depth(&fox_img->instances[id], 1);
    //         // }
    //         j++;
    //         x += 64;
    //     }
    //     i++;
    //     y += 64;
    //     j = 0;
    //     x = 0;
    // }