/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_map_checker.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 14:51:33 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/22 18:32:34 by svrielin      ########   odam.nl         */
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

void	check_row(char *row, int rowlen, t_entity *entity)
{
	int i;

	i = 0;
	if(row[0] != '1' && row[rowlen] != '1')
		so_long_error(MAP_WALLS, NULL); //Error not surrounded by walls
	while(row[i] != '\0')
	{
		if (valid_char(row[i]) == false)
			so_long_error(MAP_CHAR, NULL);
		if (row[i] == 'P') //should I check for 'P' and 'p'?
			entity->player++;
		else if (row[i] == 'E')
			entity->exit++;
		else if (row[i] == 'C')
			entity->collectible++;
		i++;
	}
}

void	check_entities(t_entity *entity)
{
	if (entity->player != 1)
		so_long_error(MAP_PLAYER, NULL);
	if (entity->exit != 1)
		so_long_error(MAP_EXIT, NULL);
	if (entity->collectible < 1)
		so_long_error(MAP_COLL, NULL);
}

void	check_valid_map(t_map *map)
{
	t_entity entity;
	int row;
	entity.player = 0;
	entity.exit = 0;
	entity.collectible = 0;
	row = 0;
	while (row < (map->rowlen))
	{
		if (row == 0 || row == (map->rowlen - 1))
		{
			if (check_all_wall(map->grid[row]) == false)
				so_long_error(MAP_WALLS, NULL);
		}
		else
			check_row(map->grid[row], map->rowlen, &entity);
		row++;
	}
	check_entities(&entity);
}

	//check if there are no other characters than 0/1/P/E/C
	//check if the map is surrounded by walls
	//check if there is 1 player
	//check if there is 1 exit
	//check if there's 1 or more collectibles
	//check if there's a valid path in the map