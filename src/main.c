/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 13:09:30 by svrielin      #+#    #+#                 */
/*   Updated: 2022/11/06 15:54:13 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int32_t	main(int argc, char **argv)
{
	if (argc != 2)
		ft_printf("Give 1 path to file map\n");
	else
		so_long(argv[1]);
	system("leaks so_long");
	return (0);
}
