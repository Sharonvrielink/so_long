/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_reader.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 18:10:25 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/08 21:11:03 by svrielin      ########   odam.nl         */
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

void	read_map(const char *map_file)
{
	int		fd;
	t_list	*map_list = NULL;
	char *line;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return ;
	while(true)
	{
		line = get_next_line(fd);
		if(line)
			ft_lstadd_back(&map_list, ft_lstnew(line));
		else
			break ;
	}
	print_lst(map_list);
}
