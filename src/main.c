/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmid <marvin@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:45:06 by eschmid           #+#    #+#             */
/*   Updated: 2022/11/08 16:35:21 by eschmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_monster_pos(t_game *a, char *line, char *line_up, char *line_down)
{
	int	move_done;

	move_done = 0;
	if (a->player.y < a->monster[a->index_monster].y
		&& check_monster_move(a, line_up, 0) == 1)
		move_done = monster_move_ud(a, 'U');
	if (a->player.y > a->monster[a->index_monster].y
		&& check_monster_move(a, line_down, 0) == 1)
		move_done = monster_move_ud(a, 'D');
	if (move_done != 1)
	{
		if (a->player.x < a->monster[a->index_monster].x
			&& check_monster_move(a, line, -1) == 1)
			monster_move_lr(a, 'L');
		if (a->player.x > a->monster[a->index_monster].x
			&& check_monster_move(a, line, 1) == 1)
			monster_move_lr(a, 'R');
		if ((check_monster_move(a, line, -1) != 1
				&& check_monster_move(a, line_up, 0) != 1)
			&& move_done != 1)
			if (check_monster_move(a, line_down, 0) == 1)
				monster_move_lr(a, 'D');
	}
}

void	put_image(t_mlx *a, void *img, int x, int y)
{
	mlx_put_image_to_window(a->ptr, a->window, img, x * 32, y * 32);
}

void	init_struct(t_game *struc)
{
	struc->mapi.x = 0;
	struc->mapi.y = 0;
	struc->monster = NULL;
	struc->coll = NULL;
	struc->player_moves = 0;
}

int	so_long(const char *arg)
{
	t_game	x;

	init_struct(&x);
	if (check_map(arg))
	{
		if (map_size_error(arg, &x.mapi) == 0)
			return (ft_printf("%s\n", "mauvaise map :("));
		x.map = maplloc(arg, x.mapi.y);
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
		return (0);
	}
	else
		return (ft_printf("Error\nNeed a valid map\n"));
}
