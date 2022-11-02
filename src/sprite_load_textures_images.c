/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_load_textures_images.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 14:59:58 by svrielin      #+#    #+#                 */
/*   Updated: 2022/11/02 13:58:54 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

const char	*texture_path(t_sprite_code sprite)
{
	const char *texture_path[] = {
		"textures/Grass_Texture.png",
		"textures/Hedge.png",
		"textures/Bush.png",
		"textures/Chick.png",
		"textures/Chick_Dead.png",
		"textures/Flag.png",
		"textures/Fox_Up.png",
		"textures/Fox_Down.png",
		"textures/Fox_Left.png",
		"textures/Fox_Right.png",
	};

	return (texture_path[sprite]);
}

void	load_textures(t_sprite *sprite)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		sprite->texture_array[i] = mlx_load_png(texture_path(i));
		if (sprite->texture_array[i] == NULL)
			return ; // add error message for something wrong with texture
		i++;
	}
}

void	load_images(mlx_t *mlx, t_sprite *sprite)
{
	sprite->space_img = mlx_texture_to_image(mlx, sprite->texture_array[GRASS]);
	sprite->wall_img = mlx_texture_to_image(mlx, sprite->texture_array[HEDGE]);
	sprite->bush_img = mlx_texture_to_image(mlx, sprite->texture_array[BUSH]);
	sprite->chick_img = mlx_texture_to_image(mlx, sprite->texture_array[CHICK]);
	sprite->dead_img = mlx_texture_to_image(mlx, sprite->texture_array[CHICK_DEAD]);
	sprite->exit_img = mlx_texture_to_image(mlx, sprite->texture_array[FLAG]);
	sprite->fox_img = mlx_texture_to_image(mlx, sprite->texture_array[FOX_DOWN]);
}
