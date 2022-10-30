/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   copy_grid.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 21:24:15 by svrielin      #+#    #+#                 */
/*   Updated: 2022/10/30 21:25:08 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

char	**copy_grid(char **grid, int rowlen)
{
	char	**copy;
	int		row;

	row = 0;
	copy = malloc(rowlen * sizeof(char *));
	if (!copy)
		return (NULL);
	while (row < rowlen)
	{
		copy[row] = ft_strdup(grid[row]);
		row++;
	}
	return (copy);
}
