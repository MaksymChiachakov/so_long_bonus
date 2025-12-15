/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:38:37 by mchiacha          #+#    #+#             */
/*   Updated: 2025/12/15 13:15:14 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#include "../ft_printf/ft_printf.h"

void	finish_game(t_data *data)
{
	if (!data)
		return ;
	write(1, "Congratulations!\n", 17);
	ft_printf("You did it with %d moves\n", data->moves);
	clean_and_exit(data, NULL);
}

void	pixel_to_tile(int px, int py, int *tx, int *ty)
{
	if (!tx || !ty)
		return ;
	*tx = px / TILE_SIZE;
	*ty = py / TILE_SIZE;
}

void	my_test_func(t_data *data, int new_x, int new_y)
{
	int		tile_x;
	int		tile_y;
	char	tile;

	if (!data || !data->map)
		return ;
	pixel_to_tile(new_x, new_y, &tile_x, &tile_y);
	if (tile_x >= 0 && tile_x < data->cols && tile_y >= 0
		&& tile_y < data->rows)
	{
		tile = data->map[tile_y][tile_x];
		if (tile != '1')
		{
			data->player_x = new_x;
			data->player_y = new_y;
			if (tile == 'C')
			{
				data->map[tile_y][tile_x] = '0';
				data->collectibles--;
			}
			if (tile == 'E' && data->collectibles == 0)
				finish_game(data);
			render_map2(data, data->player_x, data->player_y);
		}
	}
}

void	my_test_second_func(t_data *data, int keysym)
{
	if (!data)
		return ;
	if (keysym == XK_a || keysym == XK_A || keysym == XK_Left)
		affiche(data, 1);
	if (keysym == XK_d || keysym == XK_D || keysym == XK_Right)
		affiche(data, 2);
	if (keysym == XK_w || keysym == XK_W || keysym == XK_Up)
		affiche(data, 3);
	if (keysym == XK_s || keysym == XK_S || keysym == XK_Down)
		affiche(data, 4);
}

int	handle_keypress(int keysym, void *param)
{
	t_data	*data;
	t_pt	xy;
	t_pt	pxpy;

	xy.x = -1;
	xy.y = -1;
	pxpy.x = -1;
	pxpy.y = -1;
	data = (t_data *)param;
	if (!data)
		return (0);
	if (keysym == XK_Escape)
		return (clean_and_exit(data, "Goodbye\n"), 0);
	my_test_second_func(data, keysym);
	my_new_best_func(data, 0, xy, pxpy);
	render_map2(data, data->player_x, data->player_y);
	return (0);
}
