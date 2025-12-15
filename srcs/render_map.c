/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:50:49 by mchiacha          #+#    #+#             */
/*   Updated: 2025/12/15 10:52:58 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	my_best_func(char c, t_data *data, int px, int py)
{
	if (!data || !data->mlx_ptr || !data->win_ptr)
		return ;
	if (c == 'C')
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->floor, px, py);
		if (data->treasure)
			put_image_with_transparency(data, data->treasure, px, py);
	}
	else if (c == 'E')
	{
		if (data->collectibles == 0 && data->exit_open)
			put_image_with_transparency(data, data->exit_open, px, py);
		else if (data->collectibles > 0 && data->exit_close)
			put_image_with_transparency(data, data->exit_close, px, py);
	}
	else if (c == '0' && data->floor)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->floor, px, py);
}

void	my_new_best_func(t_data *data, int test, t_pt xy, t_pt pxpy)
{
	char	c;

	while (++xy.y < data->rows)
	{
		xy.x = -1;
		while (++xy.x < data->cols)
		{
			c = data->map[xy.y][xy.x];
			pxpy.x = data->offset_x + xy.x * TILE_SIZE;
			pxpy.y = data->offset_y + xy.y * TILE_SIZE;
			if (c == '1' && data->wall)
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->wall, pxpy.x, pxpy.y);
				if (test == 0)
				{
					render_hud(data, pxpy.x + 32, pxpy.y + 34);
					test = 1;
				}
			}
			else
				my_best_func(c, data, pxpy.x, pxpy.y);
		}
	}
}

void	render_map(t_data *data)
{
	t_pt	xy;
	t_pt	pxpy;

	xy.x = -1;
	xy.y = -1;
	pxpy.x = -1;
	pxpy.y = -1;
	if (!data || !data->map || !data->mlx_ptr || !data->win_ptr)
		return ;
	my_new_best_func(data, 0, xy, pxpy);
}
