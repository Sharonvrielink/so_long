/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_path_checker.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 19:02:05 by svrielin      #+#    #+#                 */
/*   Updated: 2022/10/20 12:53:52 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	locate_start_finish(t_map *map)
{
	int		row;
	int		column;

	row = 0;
	column = 0;
	while(row < map->rowlen)
	{
		while(column < map->columnlen)
		{
			if (map->grid[row][column] == 'P')
			{
				map->startrow = row;
				map->startcolumn = column;
			}
			if (map->grid[row][column] == 'E')
			{
				map->exitrow = row;
				map->exitcolumn = column;
			}
			column++;
		}
		column = 0;
		row++;
	}
}

char **copy_grid(char **grid, int rowlen)
{
	char	**copy;
	int		row;

	row = 0;
	copy = malloc(rowlen * sizeof(char *));
	while (row < rowlen)
	{
		copy[row] = ft_strdup(grid[row]);
		printf("%s\n", copy[row]);
		row++;
	}
	return (copy);
}

bool find_path(int row, int col, t_map *map, char **gridcopy)
{
	//Check if the exit is reached
	if(row == map->exitrow && col == map->exitcolumn)
		return true;
	if(row > 0 && col > 0 && row < (map->rowlen - 1) && col < (map->columnlen - 1) && gridcopy[row][col] != '1' && map->grid[row][col] != '1')
	{
		gridcopy[row][col] = '1';
		printf("row %d: %s\n", row, gridcopy[row]);
		if(find_path(row + 1, col, map, gridcopy))
			return true;
		if(find_path(row, col + 1, map, gridcopy))
			return true;
		if(find_path(row - 1, col, map, gridcopy))
			return true;
		if(find_path(row, col - 1, map, gridcopy))
			return true;
		gridcopy[row][col] = map->grid[row][col];
		return false;
	}
	return false;
}

void check_valid_path(t_map *map)
{
	char **gridcopy;
	bool valid;
	
	gridcopy = copy_grid(map->grid, map->rowlen);
	locate_start_finish(map);
	printf("Location start: [%d][%d]\n", map->startrow, map->startcolumn);
	printf("Location exit: [%d][%d]\n", map->exitrow, map->exitcolumn);
	valid = find_path(map->startrow, map->startcolumn, map, gridcopy);
	int row = 0;
	while (row < map->rowlen)
	{
		free(gridcopy[row]);
		row++;
	}
	if (valid == true)
		printf("Valid path!\n");
	if (valid == false)
		so_long_error(MAP_PATH, map);
}