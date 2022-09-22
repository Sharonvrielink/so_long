/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_map_checker.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 14:51:33 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/22 15:02:24 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

bool	valid_char(char c)
{
	if (c != '0' && c != '1' && c != 'P' && c != 'E' && c != 'C')
		return false;
	else
		return true;
}

bool	check_all_wall(char *row)
{
	int i; 

	i = 0;
	while (row[i] != '\0')
	{
		if (row[i] != '1')
			return false;
		i++;
	}
	return true;
}

t_error	check_row(char *row, int rowlen, t_entity *entity)
{
	int i;

	i = 0;
	if(row[0] != '1' && row[rowlen] != '1')
		return (so_long_error(MAP_WALLS)); //Error not surrounded by walls
	while(row[i] != '\0')
	{
		if (valid_char(row[i]) == false)
			return (so_long_error(MAP_CHAR));
		if (row[i] == 'P') //should I check for 'P' and 'p'?
			entity->player++;
		else if (row[i] == 'E')
			entity->exit++;
		else if (row[i] == 'C')
			entity->collectible++;
		i++;
	}
	return SUCCES;
}

void	check_valid_map(t_map *map)
{
	t_entity entity;
	int row;
	printf("in check_valid_map\n");
	entity.player = 0;
	entity.exit = 0;
	entity.collectible = 0;
	row = 0;
	printf("columnlen = %d\n", map->rowlen);
	while (row < (map->rowlen))
	{
		printf("in while loop rows\n");
		if (row == 0 || row == (map->rowlen - 1))
		{
			if (check_all_wall(map->grid[row]) == false)
				so_long_error(MAP_WALLS);
			printf("all wall is true\n");
		}
		else
			check_row(map->grid[row], map->rowlen, &entity);
		row++;
	}
	//check if there are no other characters than 0/1/P/E/C
	//check if the map is surrounded by walls
	//check if there is 1 player
	//check if there is 1 exit
	//check if there's 1 or more collectibles
	//check if there's a valid path in the map

	
}
