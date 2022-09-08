/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_reader.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 18:10:25 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/08 19:18:44 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_map(const char *map_file)
{
	int		fd;
	t_list	*map_list;

	fd = open(map_file, O_RDONLY);
	if (!fd)
		return (NULL);
	map_list = ft_lstnew(get_next_line(fd));
	
}