/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 09:27:12 by svrielin      #+#    #+#                 */
/*   Updated: 2022/07/19 16:49:17 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <string.h> // for memset (later use libft!)
//#include <stdio.h>
#define WIDTH 1080
#define HEIGHT 1080
#define BPP sizeof(int32_t)

//gcc main.c MLX42/libmlx42.a -I include -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

static	mlx_image_t *sprite_img;
static	mlx_image_t *fox_img;

void	hook(void *param)
{
	mlx_t	*mlx;
	mlx_texture_t	*foxdown_texture;
	mlx_texture_t	*foxup_texture;
	mlx_texture_t	*foxleft_texture;
	mlx_texture_t	*foxright_texture;

	foxdown_texture = mlx_load_png("Fox_Down.png");
	foxup_texture = mlx_load_png("Fox_Up.png");
	foxleft_texture = mlx_load_png("Fox_Left.png");
	foxright_texture = mlx_load_png("Fox_Right.png");
	
	mlx = param; //mlx is nu void pointer? waarom?
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
	if (mlx_is_key_down(param, MLX_KEY_UP))
	{
		mlx_draw_texture(fox_img, foxup_texture, (fox_img->instances[0].x), (fox_img->instances[0].y));
		fox_img->instances[0].y -= 5;
		//fox_img = mlx_texture_to_image(mlx, foxup_texture);
	}
	if (mlx_is_key_down(param, MLX_KEY_DOWN))
	{
		//fox_img = mlx_texture_to_image(mlx, foxdown_texture);
		fox_img->instances[0].y += 5;
	}
	if (mlx_is_key_down(param, MLX_KEY_LEFT))
		fox_img->instances[0].x -= 5;
	if (mlx_is_key_down(param, MLX_KEY_RIGHT))
		fox_img->instances[0].x += 5;
}

//int32_t is the C standard for an int with a specified size of 32 bits (int varies between 16 & 32)
int32_t main(void)
{
	mlx_t	*mlx;
	mlx_texture_t	*foxdown_texture;
	
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE); //These EXIT statuses failure is 1 succes = 0 are define in stdlib.h
	
	foxdown_texture = mlx_load_png("Fox_Down.png");
	fox_img = mlx_texture_to_image(mlx, foxdown_texture);

	mlx_image_to_window(mlx, fox_img, 0, 0);
	
	sprite_img = mlx_new_image(mlx, 128, 128); //Creates a new image
	memset(sprite_img->pixels, 255, sprite_img->width * sprite_img->height * BPP);//set the channels of each pixel in the image to the maximum byte value of 255
	mlx_image_to_window(mlx, sprite_img, 0, 0); //Adds an image to the render queue
	//mlx_put_pixel(sprite_img, 64, 64, 0xeb4034FF); //Single red pixel in the middle of image
	
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx); //Rendering of mlx, which loops until the window is closed
	//mlx_delete_image(mlx, sprite_img); //Cleanup the image after exit
	mlx_terminate(mlx);
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