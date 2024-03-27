/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmid <marvin@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:32:20 by eschmid           #+#    #+#             */
/*   Updated: 2022/11/07 18:41:23 by eschmid         ###   ########.fr       */
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
		if (a->player.x == a->coll[a->index_coll].x && a->player.y == a->coll[a->index_coll].y)
		{
			a->coll[a->index_coll].x = 0;
			a->coll[a->index_coll].y = 0;
			a->count_coll--;
		}
	}
	a->index_monster = -1;
	while (++a->index_monster < a->count_monster)
	{
		if (a->player.x == a->monster[a->index_monster].x
			&& a->player.y == a->monster[a->index_monster].y)
			close_game(*a, 2);
	}
}

void	monster_ia(t_game *a)
{
	char	*line;
	char	*line_up;
	char	*line_down;

	a->index_monster = -1;
	while (++a->index_monster < a->count_monster)
	{
		line = ft_strdup(a->map[a->monster[a->index_monster].y]);
		line_up = ft_strdup(a->map[a->monster[a->index_monster].y - 1]);
		line_down = ft_strdup(a->map[a->monster[a->index_monster].y + 1]);
		check_monster_pos(a, line, line_up, line_down);
		free (line);
		free (line_up);
		free (line_down);
	}
}

int	monster_move_ud(t_game *a, int i)
{
	size_t	j;

	j = a->index_monster;
	if (i == 'U')
	{
		clear_image(a->mlx, a->monster[j], a->images);
		a->monster[a->index_monster].y -= 1;
		put_image(&a->mlx, a->images.monster, a->monster[j].x, a->monster[j].y);
		return (1);
	}
	if (i == 'D')
	{
		clear_image(a->mlx, a->monster[j], a->images);
		a->monster[a->index_monster].y += 1;
		put_image(&a->mlx, a->images.monster, a->monster[j].x, a->monster[j].y);
		return (1);
	}
	return (0);
}
