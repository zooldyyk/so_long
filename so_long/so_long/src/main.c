/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserafim <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:45:06 by rserafim          #+#    #+#             */
/*   Updated: 2022/04/11 15:45:13 by rserafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_struct(t_game *struc)
{
	struc->mapi.x = 0;
	struc->mapi.y = 0;
	struc->monster = NULL;
	struc->coll = NULL;
}

int	so_long(const char *arg)
{
	t_game	x;

	init_struct(&x);
	if (check_map(arg))
	{
		if (map_size_error(arg, &x.mapi) == 0)
			return (ft_printf("%s\n", "mauvaise map :("));
		x.map = maplloc(arg);
		entity_counter(&x);
		init_entity(&x);
		window_init(x);
		return (1);
	}
	else
		return (ft_printf("Error\nNeed a valid map\n"));
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		(so_long(av[1]));
	}
	else
		return (ft_printf("Error\nNeed a valid map\n"));
}
