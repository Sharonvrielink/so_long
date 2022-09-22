/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 14:18:03 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/22 15:29:10 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	so_long_error(t_error errorcode)
{
	if (errorcode == MAP_WALLS)
		printf("Error: map unvalid, not surrounded by walls\n");
	if (errorcode == MAP_CHAR)
		printf("Error: map unvalid, unvalid char found\n");
	// delete_img(game->mlx, &game->sprite);
	// mlx_terminate(game->mlx);
	exit(EXIT_FAILURE);
}