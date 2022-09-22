/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 14:18:03 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/22 18:58:06 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

char *error_messages(t_error errorcode)
{
	char	*message[] = {
		"Exit: Succes!\n",
		"Error: map invalid, not surrounded by walls\n",
		"Error: map invalid, invalid char found\n",
		"Error: map invalid, map should contain 1 player\n",
		"Error: map invalid, map should contain 1 exit\n",
		"Error: map invalid, map should contain 1 or more collectibles\n",
		"Error: map invalid, too big for current screen size\n",
	};
	return (message[errorcode]);
}

int	so_long_error(t_error errorcode, t_game *game)
{
	ft_putstr_fd(error_messages(errorcode), 1);
	if (game != NULL)
	{
		delete_img(game->mlx, &game->sprite);
		mlx_terminate(game->mlx);
	}
	exit(EXIT_FAILURE);
}