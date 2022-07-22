/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 09:27:12 by svrielin      #+#    #+#                 */
/*   Updated: 2022/07/21 17:26:02 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <string.h> // for memset (later use libft!)
#include <stdio.h>
#define WIDTH 1080
#define HEIGHT 1080
#define BPP sizeof(int32_t)

//gcc main.c MLX42/libmlx42.a -I include -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

typedef enum e_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
} t_direction;

typedef struct s_fox
{
	t_direction	direction;
	mlx_texture_t	*down_texture;
	mlx_texture_t	*up_texture;
	mlx_texture_t	*left_texture;
	mlx_texture_t	*right_texture;
	mlx_image_t *fox_img;
}	t_fox;

typedef struct s_game_data
{
	t_fox *main_fox;
	mlx_t *mlx;
}	t_game_data;

static	mlx_image_t *sprite_img;

void	load_fox_textures(t_fox *fox)
{
	fox->down_texture = mlx_load_png("Fox_Down.png");
	fox->up_texture = mlx_load_png("Fox_Up.png");
	fox->left_texture = mlx_load_png("Fox_Left.png");
	fox->right_texture = mlx_load_png("Fox_Right.png");
}
void	hook(void *param)
{
	t_game_data *game_data;
	mlx_t	*mlx;
	t_fox 	*fox;
	game_data = param;
	mlx = game_data->mlx; //mlx is nu void pointer? waarom?
	fox = game_data->main_fox;
	load_fox_textures(fox);
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
			if (fox->direction != UP)
			{
				uint32_t tx;
				uint32_t ty;
				tx = fox->fox_img->instances->x;
				ty = fox->fox_img->instances->y;
				fox->direction = UP;
				mlx_delete_image(mlx, fox->fox_img);
				fox->fox_img = mlx_texture_to_image(mlx, fox->up_texture);
				mlx_image_to_window(mlx, fox->fox_img, tx, ty);
			}
		//mlx_image_to_window(mlx, fox_img, (fox_img->instances[0].x), (fox_img->instances[0].y));
		fox->fox_img->instances[0].y -= 5;
		//fox_img = mlx_texture_to_image(mlx, foxup_texture);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		if (fox->direction != DOWN)
			{
				uint32_t tx;
				uint32_t ty;
				tx = fox->fox_img->instances->x;
				ty = fox->fox_img->instances->y;
				fox->direction = DOWN;
				mlx_delete_image(mlx, fox->fox_img);
				fox->fox_img = mlx_texture_to_image(mlx, fox->down_texture);
				mlx_image_to_window(mlx, fox->fox_img, tx, ty);
			}
		fox->fox_img->instances[0].y += 5;

	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		if (fox->direction != LEFT)
		{
			uint32_t tx;
			uint32_t ty;
			tx = fox->fox_img->instances->x;
			ty = fox->fox_img->instances->y;
			fox->direction = LEFT;
			mlx_delete_image(mlx, fox->fox_img);
			fox->fox_img = mlx_texture_to_image(mlx, fox->left_texture);
			mlx_image_to_window(mlx, fox->fox_img, tx, ty);
		}
		fox->fox_img->instances[0].x -= 5;
		//mlx_draw_texture(sprite_img, foxdown_texture, 0, 0);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		if (fox->direction != RIGHT)
		{
			uint32_t tx;
			uint32_t ty;
			fox->direction = RIGHT;
			tx = fox->fox_img->instances->x;
			ty = fox->fox_img->instances->y;
			mlx_delete_image(mlx, fox->fox_img);
			fox->fox_img = mlx_texture_to_image(mlx, fox->right_texture);
			mlx_image_to_window(mlx, fox->fox_img, tx, ty);
		}
		fox->fox_img->instances[0].x += 5;
	}
}

//int32_t is the C standard for an int with a specified size of 32 bits (int varies between 16 & 32)
int32_t main(void)
{
	t_game_data game_data;

	
	game_data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!game_data.mlx)
		exit(EXIT_FAILURE); //These EXIT statuses failure is 1 succes = 0 are define in stdlib.h
	
	game_data.main_fox->fox_img = mlx_new_image(game_data.mlx, 128, 128);
	memset(game_data.main_fox->fox_img->pixels, 255, game_data.main_fox->fox_img->width * game_data.main_fox->fox_img->height * BPP);
	mlx_image_to_window(game_data.mlx, game_data.main_fox->fox_img, 0, 0);
	//mlx_draw_texture(fox_img, foxdown_texture, 0, 0);
	
	//sprite_img = mlx_new_image(game_data.mlx, 128, 128); //Creates a new image
	//memset(sprite_img->pixels, 255, sprite_img->width * sprite_img->height * BPP);//set the channels of each pixel in the image to the maximum byte value of 255
	//mlx_image_to_window(game_data.mlx, sprite_img, 0, 0); //Adds an image to the render queue
	//mlx_put_pixel(sprite_img, 64, 64, 0xeb4034FF); //Single red pixel in the middle of image
	
	mlx_loop_hook(game_data.mlx, &hook, &game_data);
	mlx_loop(game_data.mlx); //Rendering of mlx, which loops until the window is closed
	mlx_delete_image(game_data.mlx, game_data.main_fox->fox_img); //Cleanup the image after exit
	mlx_terminate(game_data.mlx);
	return (EXIT_SUCCESS);
}

// #include "mlx.h"

// //compile: cc -Imlx main.c -Lmlx -lmlx -framework OpenGL -framework AppKit

// typedef struct s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }		t_data;

// 	/*Own pixel_put to write pixels to the image
// 	Since pixel+put is very slow because it pushes the pixel instantly before the frame is rendered
// 	Instead with this function buffers all pixels to an image, which we will then push to the window*/
// void	pixel_to_image_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;
// 	int		linelenght_offset;

// 	//The offset is necessary to know where to write, since line_length differs from window widt;
// 	linelenght_offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	dst = data->addr + linelenght_offset;
// 	*(unsigned int*)dst = color;
// }
// int main(void)
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// 	t_data	img;

// 	mlx_ptr = mlx_init();
// 	win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "so_long");
// 	img.img = mlx_new_image(mlx_ptr, 1920, 1080);
// 	//Returns information (in parameters) about the created image so it can be modified
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
// 	//Use or own pixel_put to write pixels to the image
// 	pixel_to_image_put(&img, 50, 50, 0x00FF0000);
// 	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
// 	mlx_loop(mlx_ptr);
// }