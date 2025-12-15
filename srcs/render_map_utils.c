/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:54:42 by mchiacha          #+#    #+#             */
/*   Updated: 2025/12/15 13:14:52 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	render_hud(t_data *d, int px, int py)
{
	char	*str;

	str = ft_itoa(d->moves);
	mlx_string_put(d->mlx_ptr, d->win_ptr,
		px, py, 0xFF0000, str);
	free(str);
}

void	render_map2(t_data *d, int x, int y)
{
	int	idx;

	idx = 0;
	if (!d || !d->mlx_ptr || !d->win_ptr || !d->butterfly[0])
	{
		clean_and_exit(d, NULL);
		return ;
	}
	if (d->butterfly[0])
	{
		idx = (d->frame / 6) % 7;
		if (idx >= 0 && idx < 7 && d->butterfly[idx])
		{
			put_image_with_transparency(d, d->butterfly[idx],
				d->offset_x + x, d->offset_y + y);
		}
	}
	usleep(16000);
}
