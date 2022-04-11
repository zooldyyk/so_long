/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmid <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:09:26 by eschmid           #+#    #+#             */
/*   Updated: 2022/04/11 16:14:14 by eschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free(char *str)
{
	int	i;

	i = 0;
	while (str[i++] != '\0')
		free(&str[i]);
}

char	**maplloc(const char *arg)
{
	int			fd;
	char		**tab;
	const char	*line;
	const char	*save;

	save = "";
	fd = open(arg, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		line = ft_strjoin_char((char *)line, 'S');
		save = ft_strjoin(save, line);
		line = get_next_line(fd);
	}	
	return (tab = ft_split(save, 'S'));
}
