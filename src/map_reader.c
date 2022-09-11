/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_reader.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 18:10:25 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/11 16:45:26 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	print_lst(t_list *lst)
{
	while (lst)
	{
		printf("Content lst = %s", lst->content);
		lst = lst->next;
	}
}

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
			return (-1); //Error: map is not rectangular
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

void	printtwodarray(char **twod_array, int rowlen, int columnlen)
{
	int	row;
	int	column;

	row = 0;
	column = 0;
	printf("\n");
	while (row < rowlen)
	{
		while (column < ((int)columnlen))
		{
			printf("[%c]", twod_array[row][column]);
			column++;
		}
		printf("\n");
		column = 0;
		row++;
	}
}

void	read_map(const char *map_file, t_map *map)
{
	int		fd;
	int		row;
	int		column;
	t_list	*map_list;

	map_list = NULL;
	row = 0;
	column = 0;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return ; //Error: check map path, could not open the map file
	map->columnlen = load_into_lst(fd, &map_list);
	map->rowlen = ft_lstsize(map_list);
	map->grid = malloc((map->rowlen + 1) * sizeof(char *));
	while (row < (map->rowlen))
	{
		map->grid[row] = ft_strndup(map_list->content, map->columnlen);
		map_list = map_list->next;
		row++;
	}
	ft_lstclear(&map_list, free);
	return ;
}
