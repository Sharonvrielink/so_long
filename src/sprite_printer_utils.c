/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_printer_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 14:59:58 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/21 15:19:45 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	load_textures(t_sprite *sprite)
{
	sprite->space_texture = mlx_load_png("textures/Grass_Texture.png");
	sprite->wall_texture = mlx_load_png("textures/Hedge.png");
	sprite->rosewall_texture = mlx_load_png("textures/Hedge_Roses.png");
	sprite->bush_texture = mlx_load_png("textures/Bush.png");
	sprite->collectible_texture = mlx_load_png("textures/Chick.png");
	sprite->collected_texture = mlx_load_png("textures/Chick_Dead.png");
	sprite->exit_texture = mlx_load_png("textures/Flag.png");
	sprite->foxdown_texture = mlx_load_png("textures/Fox_Down.png");
	sprite->foxup_texture = mlx_load_png("textures/Fox_Up.png");
	sprite->foxleft_texture = mlx_load_png("textures/Fox_Left.png");
	sprite->foxright_texture = mlx_load_png("textures/Fox_Right.png");
}

void	load_images(mlx_t *mlx, t_sprite *sprite)
{
	sprite->space_img = mlx_texture_to_image(mlx, sprite->space_texture);
	sprite->wall_img = mlx_texture_to_image(mlx, sprite->wall_texture);
	sprite->rosewall_img = mlx_texture_to_image(mlx, sprite->rosewall_texture);
	sprite->bush_img = mlx_texture_to_image(mlx, sprite->bush_texture);
	sprite->collectible_img = mlx_texture_to_image(mlx, sprite->collectible_texture);
	sprite->collected_img = mlx_texture_to_image(mlx, sprite->collected_texture);
	sprite->exit_img = mlx_texture_to_image(mlx, sprite->exit_texture);
	sprite->fox_img = mlx_texture_to_image(mlx, sprite->foxdown_texture);
}
