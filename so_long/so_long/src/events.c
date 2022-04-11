/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmid <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:32:20 by eschmid           #+#    #+#             */
/*   Updated: 2022/04/11 16:07:45 by eschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_entity(t_game *a)
{
	a->monster = malloc(sizeof(a->monster) * a->count_monster);
	a->coll = malloc(sizeof(a->coll) * a->count_coll);
}

void	entity_counter(t_game *x)
{
	t_coord	index;

	index.y = 0;
	x->count_monster = 0;
	x->count_coll = 0;
	while (x->map[index.y])
	{
		index.x = 0;
		while (x->map[index.y][index.x] != '\0')
		{
			if (x->map[index.y][index.x] == 'C')
				x->count_coll++;
			if (x->map[index.y][index.x] == 'M')
				x->count_monster++;
			index.x++;
		}
		index.y++;
	}
}

void	event_manager(t_game *a)
{
	a->index_coll = -1;
	while (++a->index_coll <= a->count_coll)
	{
		if (a->player.x == a->coll[a->index_coll].x
			&& a->player.y == a->coll[a->index_coll].y)
		{
			a->coll[a->index_coll].x = 0;
			a->coll[a->index_coll].y = 0;
			a->count_coll--;
			ft_printf("coll restants : %zu\n", a->count_coll);
		}
	}
	a->index_monster = -1;
	while (++a->index_monster < a->count_monster)
	{
		if (a->player.x == a->monster[a->index_monster].x
			&& a->player.y == a->monster[a->index_monster].y)
			close_game(a->mlx, 2);
	}
}

void	monster_ia(t_game *a)
{
	int		move_done;
	char	*line;
	char	*line_up;
	char	*line_down;

	a->index_monster = -1;
	while (++a->index_monster < a->count_monster)
	{
		move_done = 0;
		line = ft_strdup(a->map[a->monster[a->index_monster].y]);
		line_up = ft_strdup(a->map[a->monster[a->index_monster].y - 1]);
		line_down = ft_strdup(a->map[a->monster[a->index_monster].y + 1]);
		if (a->player.y < a->monster[a->index_monster].y
			&& check_monster_move(a, line_up, 0) == 1)
			move_done = monster_move(a, 'U');
		if (a->player.y > a->monster[a->index_monster].y
			&& check_monster_move(a, line_down, 0) == 1)
			move_done = monster_move(a, 'D');
		if (move_done != 1)
		{
			if (a->player.x < a->monster[a->index_monster].x
				&& check_monster_move(a, line, -1) == 1)
				monster_move(a, 'L');
			if (a->player.x > a->monster[a->index_monster].x
				&& check_monster_move(a, line, 1) == 1)
				monster_move(a, 'R');
			if ((check_monster_move(a, line, -1) != 1
					&& check_monster_move(a, line_up, 0) != 1)
				&& move_done != 1)
				if (check_monster_move(a, line_down, 0) == 1)
					monster_move(a, 'D');
		}
	}
}

int	check_monster_move(t_game *a, char *line, int i)
{
	size_t	current_monster;
	size_t	other_monsters;

	current_monster = a->index_monster;
	other_monsters = -1;
	while (a->monster[current_monster].x != a->monster[++other_monsters].x)
	{
		if (a->monster[current_monster].x + i == a->monster[other_monsters].x)
			return (0);
	}
	a->index_coll = -1;
	while (++a->index_coll <= a->count_coll)
		if (a->monster[current_monster].x + i == a->coll[a->index_coll].x
			&& a->monster[current_monster].y == a->coll[a->index_coll].y)
			return (0);
	if (a->monster[current_monster].x == a->coll[a->index_coll].x
		&& a->monster[current_monster].y + i == a->coll[a->index_coll].y)
		return (0);
	if (line[a->monster[a->index_monster].x + i] == '1')
		return (0);
	if (line[a->monster[a->index_monster].x + i] == 'E')
		return (0);
	else
		return (1);
}

int	monster_move(t_game *a, int i)
{
	if (i == 'L')
	{
		clear_image(a->mlx, a->monster[a->index_monster], a->images);
		a->monster[a->index_monster].x -= 1;
		mlx_put_image_to_window(a->mlx.ptr, a->mlx.window, a->images.monster, a->monster[a->index_monster].x * 32, a->monster[a->index_monster].y * 32);
		return (1);
	}
	if (i == 'R')
	{
		clear_image(a->mlx, a->monster[a->index_monster], a->images);
		a->monster[a->index_monster].x += 1;
		mlx_put_image_to_window(a->mlx.ptr, a->mlx.window, a->images.monster, a->monster[a->index_monster].x * 32, a->monster[a->index_monster].y * 32);
		return (1);
	}
	if (i == 'U')
	{
		clear_image(a->mlx, a->monster[a->index_monster], a->images);
		a->monster[a->index_monster].y -= 1;
		mlx_put_image_to_window(a->mlx.ptr, a->mlx.window, a->images.monster, a->monster[a->index_monster].x * 32, a->monster[a->index_monster].y * 32);
		return (1);
	}
	if (i == 'D')
	{
		clear_image(a->mlx, a->monster[a->index_monster], a->images);
		a->monster[a->index_monster].y += 1;
		mlx_put_image_to_window(a->mlx.ptr, a->mlx.window, a->images.monster, a->monster[a->index_monster].x * 32, a->monster[a->index_monster].y * 32);
		return (1);
	}
	return (0);
}
