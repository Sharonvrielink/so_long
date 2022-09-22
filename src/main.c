/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 13:09:30 by svrielin      #+#    #+#                 */
/*   Updated: 2022/09/22 10:03:53 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//gcc main.c MLX42/libmlx42.a -I include -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

#include "so_long.h"

int32_t main(int argc, char **argv)
{
	if (argc < 2 || argc > 2)
		printf("Give 1 path to file map\n");
	else
    	so_long(argv[1]);
}
