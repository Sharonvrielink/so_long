/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 14:18:03 by svrielin      #+#    #+#                 */
/*   Updated: 2022/11/10 12:29:34 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

const char	*error_messages(t_error errorcode)
{
	const char	*message[] = {
		"Exit: congratulations you won the game!\n",
		"Error: map invalid, file extension should be .ber\n",
		"Error: check map path, could not open the map file\n",
		"Error: map invalid, not surrounded by walls\n",
		"Error: map invalid, invalid char found\n",
		"Error: map invalid, map should contain 1 player\n",
		"Error: map invalid, map should contain 1 exit\n",
		"Error: map invalid, map should contain 1 or more collectibles\n",
		"Error: map has no valid path to the exit\n",
		"Error: map has no valid path where everything can be collected\n",
		"Error: map invalid, too big for current screen size\n",
		"Error: map invalid, map is not rectangular\n",
		"Error: something went wrong\n",
		"Game closed\n",
	};

	return (message[errorcode]);
}

int	so_long_error_free(t_error code, t_game *game)
{
	if (game->mlx)
	{
		mlx_close_window(game->mlx);
		delete_img(game->mlx, &game->sprite);
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
	return (so_long_error(code, &game->map));
}

int	so_long_error(t_error code, t_map *map)
{
	int	row;

	row = 0;
	while (map && row < map->rowlen)
	{
		if (map->grid[row])
			free(map->grid[row]);
		row++;
	}
	if (map)
	{
		if (map->grid)
			free(map->grid);
	}
	ft_putstr_fd((char *)error_messages(code), STDERR_FILENO);
	if (code == SUCCES)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}
