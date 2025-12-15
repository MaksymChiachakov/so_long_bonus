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

void	center_map(t_data *data)
{
	int	map_width;
	int	map_height;

	if (!data)
		return ;
	map_width = data->cols * TILE_SIZE;
	map_height = data->rows * TILE_SIZE;
	data->offset_x = (WINDOW_WIDTH - map_width) / 2;
	data->offset_y = (WINDOW_HEIGHT - map_height) / 2;
	if (data->offset_x < 0)
		data->offset_x = 0;
	if (data->offset_y < 0)
		data->offset_y = 0;
}

void	render_background(t_data *data)
{
	int	y;
	int	x;

	if (!data || !data->mlx_ptr || !data->win_ptr || !data->background)
		return ;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->background, x, y);
			x += TILE_SIZE;
		}
		y += TILE_SIZE;
	}
}

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

void	my_new_best_func(t_data *data)
{
	char	c;
	int		y;
	int		x;
	int		px;
	int		py;

	if (!data || !data->map || !data->mlx_ptr || !data->win_ptr)
		return ;
	y = 0;
	while (++y < data->rows)
	{
		x = 0;
		while (++x < data->cols)
		{
			c = data->map[y][x];
			px = data->offset_x + x * TILE_SIZE;
			py = data->offset_y + y * TILE_SIZE;
			if (c == '1' && data->wall)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->wall, px, py);
			else
				my_best_func(c, data, px, py);
		}
	}
}

void	render_map(t_data *data)
{
	render_background(data);
	my_new_best_func(data);
}
