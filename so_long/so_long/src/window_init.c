/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmid <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:27:21 by eschmid           #+#    #+#             */
/*   Updated: 2022/04/11 16:38:36 by eschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_button(t_mlx *mlx)
{
	mlx_clear_window(mlx->ptr, mlx->window);
	mlx_destroy_window(mlx->ptr, mlx->window);
	exit(ft_printf("Jeu fermé\n"));
}

int	close_game(t_mlx mlx, int i)
{
	mlx_clear_window(mlx.ptr, mlx.window);
	mlx_destroy_window(mlx.ptr, mlx.window);
	if (i == 53)
		exit(ft_printf("Jeu fermé\n"));
	if (i == 1)
		exit(ft_printf("Bien vu bg\n"));
	if (i == 2)
		exit(ft_printf("C'est dangereux !\n"));
	return (0);
}

int	key_sort(int key, t_game *a)
{
	if (key == 53)
		close_game(a->mlx, 53);
	if (key == 13)
		player_up(a);
	if (key == 1)
		player_down(a);
	if (key == 0)
		player_left(a);
	if (key == 2)
		player_right(a);
	return (1);
}

void	window_init(t_game a)
{
	a.mlx.ptr = mlx_init();
	a.mlx.window = mlx_new_window(a.mlx.ptr, a.mapi.x * 32, a.mapi.y * 32, "so_long");
	init_image(&a);
	fill_map(&a, a.map);
	mlx_key_hook(a.mlx.window, key_sort, &a);
	mlx_hook(a.mlx.window, 17, 0L << 00, close_button, &a.mlx);
	mlx_loop(a.mlx.ptr);
}

void	init_image(t_game *p)
{
	p->images.sortie = mlx_xpm_file_to_image(p->mlx.ptr, "assets/sortie.xpm", &p->images.width, &p->images.height);
	p->images.player = mlx_xpm_file_to_image(p->mlx.ptr, "assets/player.xpm", &p->images.width, &p->images.height);
	p->images.wall = mlx_xpm_file_to_image(p->mlx.ptr, "assets/wall.xpm", &p->images.width, &p->images.height);
	p->images.coin = mlx_xpm_file_to_image(p->mlx.ptr, "assets/coin.xpm", &p->images.width, &p->images.height);
	p->images.monster = mlx_xpm_file_to_image(p->mlx.ptr, "assets/monster.xpm", &p->images.width, &p->images.height);
	p->images.ground = mlx_xpm_file_to_image(p->mlx.ptr, "assets/ground.xpm", &p->images.width, &p->images.height);
}

void	fill_map(t_game *p, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i++ < p->mapi.y * 32)
	{
		j = 0;
		while (j++ < p->mapi.x)
			mlx_put_image_to_window(p->mlx.ptr, p->mlx.window, p->images.ground, j * 32, i * 32);
	}
	p->index_coll = 0;
	p->index_monster = 0;
	p->mapi.y = 0;
	while (map[p->mapi.y] != NULL)
	{
		p->mapi.x = 0;
		fill_line(map[p->mapi.y], p);
		p->mapi.y++;
	}
}

void	fill_line(char *line, t_game *a)
{
	while (line[a->mapi.x] != '\0')
	{
		if (line[a->mapi.x] == 'P')
		{
			mlx_put_image_to_window(a->mlx.ptr, a->mlx.window, a->images.player, a->mapi.x * 32, a->mapi.y * 32);
			a->player.x = a->mapi.x;
			a->player.y = a->mapi.y;
		}
		if (line[a->mapi.x] == 'C')
			init_position(a, line[a->mapi.x]);
		if (line[a->mapi.x] == '1')
			mlx_put_image_to_window(a->mlx.ptr, a->mlx.window, a->images.wall, a->mapi.x * 32, a->mapi.y * 32);
		if (line[a->mapi.x] == '0')
			mlx_put_image_to_window(a->mlx.ptr, a->mlx.window, a->images.ground, a->mapi.x * 32, a->mapi.y * 32);
		if (line[a->mapi.x] == 'M')
			init_position(a, line[a->mapi.x]);
		if (line[a->mapi.x] == 'E')
			init_position(a, line[a->mapi.x]);
		a->mapi.x++;
	}
}

void	init_position(t_game *a, char c)
{
	if (c == 'C')
	{
		mlx_put_image_to_window(a->mlx.ptr, a->mlx.window, a->images.coin, a->mapi.x * 32, a->mapi.y * 32);
		a->coll[a->index_coll].x = a->mapi.x;
		a->coll[a->index_coll].y = a->mapi.y;
		a->index_coll++;
	}
	if (c == 'M')
	{
		mlx_put_image_to_window(a->mlx.ptr, a->mlx.window, a->images.monster, a->mapi.x * 32, a->mapi.y * 32);
		a->monster[a->index_monster].x = a->mapi.x;
		a->monster[a->index_monster].y = a->mapi.y;
		a->index_monster++;
	}
	if (c == 'E')
	{
		mlx_put_image_to_window(a->mlx.ptr, a->mlx.window, a->images.sortie, a->mapi.x * 32, a->mapi.y * 32);
		a->sortie.x = a->mapi.x;
		a->sortie.y = a->mapi.y;
	}
}
