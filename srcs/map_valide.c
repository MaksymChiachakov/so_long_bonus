/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:30:59 by mchiacha          #+#    #+#             */
/*   Updated: 2025/12/05 13:31:34 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	has_extension_ber(const char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len < 4)
		return (0);
	return (ft_strcmp(name + len - 4, ".ber") == 0);
}

int	check_wall(char **err_msg, char **map, int y, int x)
{
	(void)err_msg;
	if (map[y][x] != '1')
	{
		write(1, "Error\nMap is not closed by walls\n", 34);
		return (0);
	}
	return (1);
}

int	update_counts(int *p, int *e, int *c, char ch)
{
	if (ch != 'P' && ch != 'E' && ch != 'C' && ch != '1' && ch != '0')
		return (0);
	else if (ch == 'P')
		(*p)++;
	else if (ch == 'E')
		(*e)++;
	else if (ch == 'C')
		(*c)++;
	else if (ch == '1' || ch == '0')
		return (1);
	return (1);
}

int	validate_counts(t_data *data, int p, int e, int c)
{
	if (p != 1 || e != 1)
		return (0);
	if (c < 1)
		return (0);
	data->collectibles = c;
	return (1);
}

int	validate_map_structure(t_data *data, char **map, char **err_msg)
{
	int	y;
	int	x;
	int	p;
	int	e;
	int	c;

	y = -1;
	p = 0;
	e = 0;
	c = 0;
	while (++y < data->rows)
	{
		if ((int)ft_strlen(map[y]) != data->cols)
			return (clean_and_exit(data, "Error\nMap is not rectangular"), 0);
		x = -1;
		while (++x < data->cols)
		{
			if (!update_counts(&p, &e, &c, map[y][x]))
				return (clean_and_exit(data, "Error\nInvalid map\n"), 0);
			if (y == 0 || y == data->rows - 1 || x == 0 || x == data->cols - 1)
				if (!check_wall(err_msg, map, y, x))
					return (clean_and_exit(data, NULL), 0);
		}
	}
	return (validate_counts(data, p, e, c));
}
