/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmid <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:46:02 by rserafim          #+#    #+#             */
/*   Updated: 2022/04/11 16:03:19 by rserafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_need(char c, char *need)
{
	int	y;

	y = 0;
	if (c == 'P' && need[1] == '7')
		return (1);
	if (c == 'E' && need[2] == '7')
		return (1);
	while (need[y] != '\0')
	{
		if (need[y] == c)
			need[y] = '7';
		y++;
	}
	return (0);
}

int	map_size_error(const char *map_name, t_coord *p)
{
	int			fd;
	char		*line;
	static char	*need;

	need = ft_strdup("CPE");
	fd = (open(map_name, O_RDONLY));
	if (fd == -1 || fd == 0)
		return (0);
	line = get_next_line(fd);
	if (ft_char_find(line, '0'))
		return (0);
	(*p).x = ft_strlen(line);
	(*p).y = check_mid_map (line, need, fd);
	if ((*p).y == 0 || (*p).x == 0)
		return (0);
	if ((*p).y == (*p).x)
		return (0);
	if (ft_strncmp(need, "777", 3) != 0)
		return (0);
	return (1);
}

int	ft_char_find(const char *str, int to_find)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == to_find)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_line(const char *line, char *need)
{
	int	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if ((line[i + 1] == '\0' && line[i] != '1') || line[0] != '1')
			return (1);
		if (line[i] == 'P' || line[i] == 'C' || line[i] == 'E')
			if (check_need(line[i], need))
				return (1);
		if (line[i] != '0' && line[i] != '1' && line[i] != 'C')
			return (1);
		if (line[i] != 'E' && line[i] != 'M' && line[i] != 'P')
			return (1);
	}
	return (0);
}

int	check_mid_map(const char *line, char *need, int fd)
{
	int		i;
	char	*last_line;
	size_t	comp;

	i = 0;
	comp = strlen(line);
	while (line != NULL || line != (void *)0)
	{
		i++;
		last_line = ft_strdup(line);
		if (comp != ft_strlen(line))
			return (0);
		if (ft_check_line(line, need) == 1)
			return (0);
		line = get_next_line(fd);
	}
	if (ft_char_find(last_line, '0'))
		return (0);
	return (i);
}

int	check_map(const char *map)
{
	const char	*check;

	check = ft_strrchr(map, '.');
	check++;
	if (ft_strncmp(check, "ber", 3) == 0)
		return (1);
	else
		return (0);
}
