/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:49:33 by mchiacha          #+#    #+#             */
/*   Updated: 2025/12/15 10:49:51 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	load_butterfly_protection(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 7)
	{
		if (!data->butterfly[i])
			clean_and_exit(data, "Error\nFailed to load butterfly images\n");
	}
}

void	load_butterfly(t_data *data)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	data->butterfly[0] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/player.xpm", &data->player_w, &data->player_h);
	data->butterfly[1] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/player2.xpm", &w, &h);
	data->butterfly[2] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/player3.xpm", &w, &h);
	data->butterfly[3] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/player4.xpm", &w, &h);
	data->butterfly[4] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/player5.xpm", &w, &h);
	data->butterfly[5] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/player6.xpm", &w, &h);
	data->butterfly[6] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/player7.xpm", &w, &h);
	load_butterfly_protection(data);
}

int	animation_loop(t_data *d)
{
	if (!d || !d->mlx_ptr || !d->win_ptr || !d->butterfly[0])
		return (clean_and_exit(d, NULL), 0);
	d->frame++;
	if (d->frame > 1000000)
		d->frame = 0;
	render_map2(d, d->player_x, d->player_y);
	return (0);
}
