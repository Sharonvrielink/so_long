/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_reader.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 18:10:25 by svrielin      #+#    #+#                 */
/*   Updated: 2022/10/30 20:35:28 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	load_into_lst(int fd, t_list **map_list)
{
	size_t	columnlen;
	size_t	prev_columnlen;
	char	*line;

	columnlen = 0;
	prev_columnlen = 0;
	*map_list = NULL;
	while (true)
	{
		if (columnlen != prev_columnlen)
		{
			ft_lstclear(map_list, free);
			return (so_long_error(MAP_NORECTANGLE, NULL));
		}
		line = get_next_line(fd);
		if (line)
		{
			columnlen = ft_strlen(line);
			prev_columnlen = columnlen;
			ft_lstadd_back(map_list, ft_lstnew(line));
		}
		else
			break ;
	}
	return (columnlen);
}

void	construct_map_data(t_map *map, t_list **map_list, int fd)
{
	int		row;

	row = 0;
	map->columnlen = load_into_lst(fd, map_list);
	map->rowlen = ft_lstsize(*map_list);
	map->grid = malloc((map->rowlen) * sizeof(char *));
	if (!map->grid)
		return ;
	while (row < (map->rowlen))
	{
		map->grid[row] = ft_strndup((*map_list)->content, map->columnlen);
		map_list = &(*map_list)->next;
		row++;
	}
}

void	read_map(const char *map_file, t_map *map)
{
	int		fd;
	t_list	*map_list;

	map_list = NULL;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		so_long_error(MAP_FILE, NULL);
	construct_map_data(map, &map_list, fd);
	ft_lstclear(&map_list, free);
	check_valid_map(map);
	return ;
}
