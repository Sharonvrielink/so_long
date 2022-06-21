#include "mlx.h"

//compile: cc -Imlx main.c -Lmlx -lmlx -framework OpenGL -framework AppKit

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

	/*Own pixel_put to write pixels to the image
	Since pixel+put is very slow because it pushes the pixel instantly before the frame is rendered
	Instead with this function buffers all pixels to an image, which we will then push to the window*/
void	pixel_to_image_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		linelenght_offset;

	//The offset is necessary to know where to write, since line_length differs from window widt;
	linelenght_offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
	dst = data->addr + linelenght_offset;
	*(unsigned int*)dst = color;
}
int main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	img;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "so_long");
	img.img = mlx_new_image(mlx_ptr, 1920, 1080);
	//Returns information (in parameters) about the created image so it can be modified
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//Use or own pixel_put to write pixels to the image
	pixel_to_image_put(&img, 50, 50, 0x00FF0000);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
	mlx_loop(mlx_ptr);
}