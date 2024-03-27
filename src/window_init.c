/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmid <marvin@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:27:21 by eschmid           #+#    #+#             */
/*   Updated: 2022/11/08 16:36:33 by eschmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void ft_free_struct(char **tab,t_coord *coll, t_coord *monster, int y_size)
{
	free (monster);
	free (coll);
	int i;

	i = -1;
	while (++i < y_size)
	{
		free (tab[i]);
	}
	free (tab);
}
int	close_button(t_game a)
{
	mlx_clear_window(a.mlx.ptr, a.mlx.window);
	mlx_destroy_window(a.mlx.ptr, a.mlx.window);
	ft_free_struct(a.map, a.coll, a.monster,a.mapi.y);
	exit(ft_printf("Jeu fermé\n"));
}

int	close_game(t_game a, int i)
{
	mlx_clear_window(a.mlx.ptr, a.mlx.window);
	mlx_destroy_window(a.mlx.ptr, a.mlx.window);
	ft_free_struct(a.map, a.coll, a.monster,a.mapi.y);

	if (i == 53)
		exit(ft_printf("Jeu fermé\n"));
	if (i == 1)
		exit(ft_printf("Bien vu bg\n"));
	if (i == 2)
		exit(ft_printf("C'est dangereux !\n"));
	exit (0);
}

int	key_sort(int key, t_game *a)
{
	//int i;
	//char **x;

	//x = a->map;
	//free (x);

	//i = a->mapi.y;
	if (key == 53)
	{
		/*while (i++ != 0)
		{
				free(a->map);
		}
		free (a->map);*/
		close_game(*a, 53);
	}
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
	int	*x;
	int	*y;

	x = &a.mapi.x;
	y = &a.mapi.y;
	a.mlx.ptr = mlx_init();
	a.mlx.window = mlx_new_window(a.mlx.ptr, *x * 32, *y * 32, "so_long");
	init_image(&a.images, &a.mlx);
	fill_map(&a, a.map);
	count_to_window(&a.mlx, a.images.wall, &a.player_moves);
	mlx_key_hook(a.mlx.window, key_sort, &a);
	mlx_hook(a.mlx.window, 17, 0L << 00, close_button, &a);
	mlx_loop(a.mlx.ptr);
}

void	init_image(t_image *i, t_mlx *m)
{
	int	*w;
	int	*h;

	w = &i->width;
	h = &i->height;
	i->sortie = mlx_xpm_file_to_image(m->ptr, "assets/sortie.xpm", w, h);
	i->player = mlx_xpm_file_to_image(m->ptr, "assets/player.xpm", w, h);
	i->wall = mlx_xpm_file_to_image(m->ptr, "assets/wall.xpm", w, h);
	i->coin = mlx_xpm_file_to_image(m->ptr, "assets/coin.xpm", w, h);
	i->monster = mlx_xpm_file_to_image(m->ptr, "assets/monster.xpm", w, h);
	i->ground = mlx_xpm_file_to_image(m->ptr, "assets/ground.xpm", w, h);
}
