/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:30:19 by mchiacha          #+#    #+#             */
/*   Updated: 2025/12/05 13:30:21 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	**copy_map(char **map, int rows)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * rows);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

int	find_player(char **map, t_size size, int *sx, int *sy)
{
	int	y;
	int	x;

	y = 0;
	while (y < size.rows)
	{
		x = 0;
		while (x < size.cols)
		{
			if (map[y][x] == 'P')
			{
				*sx = x;
				*sy = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	set_neighbor(t_pt cur, int dir, int *nx, int *ny)
{
	if (dir == 0)
	{
		*nx = cur.x + 1;
		*ny = cur.y;
	}
	else if (dir == 1)
	{
		*nx = cur.x - 1;
		*ny = cur.y;
	}
	else if (dir == 2)
	{
		*nx = cur.x;
		*ny = cur.y + 1;
	}
	else
	{
		*nx = cur.x;
		*ny = cur.y - 1;
	}
}

void	process_neighbors(t_rc rc, t_pt cur, t_pt *queue, int *tail)
{
	int	dir;
	int	nx;
	int	ny;

	dir = 0;
	while (dir < 4)
	{
		set_neighbor(cur, dir, &nx, &ny);
		if (nx >= 0 && nx < rc.cols && ny >= 0 && ny < rc.rows)
		{
			if (rc.copy[ny][nx] != '1' && rc.copy[ny][nx] != 'X')
			{
				rc.copy[ny][nx] = 'X';
				queue[(*tail)++] = (t_pt){nx, ny};
			}
		}
		dir++;
	}
}
