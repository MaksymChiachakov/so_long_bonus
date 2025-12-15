/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canva.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:30:08 by mchiacha          #+#    #+#             */
/*   Updated: 2025/12/05 13:30:10 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	get_img_addr(t_imginfo *info, void *img)
{
	info->addr = mlx_get_data_addr(img, &info->bpp, &info->size_line,
			&info->endian);
}

void	put_visible(t_data *data, int color, int x, int y)
{
	if (color != 0xFF00FF)
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
}

void	draw_loop(t_data *data, t_imginfo *info, int x, int y)
{
	int	px;
	int	py;
	int	*pixel;

	py = 0;
	while (py < TILE_SIZE)
	{
		px = 0;
		while (px < TILE_SIZE)
		{
			pixel = (int *)(info->addr + py * info->size_line + px * (info->bpp
						/ 8));
			put_visible(data, *pixel, x + px, y + py);
			px++;
		}
		py++;
	}
}

int	put_image_with_transparency(t_data *data, void *img, int x, int y)
{
	t_imginfo	info;

	get_img_addr(&info, img);
	if (!info.addr)
		return (clean_and_exit(data, NULL), 0);
	draw_loop(data, &info, x, y);
	return (1);
}
