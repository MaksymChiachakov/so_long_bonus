/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:30:40 by mchiacha          #+#    #+#             */
/*   Updated: 2025/12/05 13:30:41 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#include "../ft_printf/ft_printf.h"

int	handle_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	clean_and_exit(data, NULL);
	return (0);
}

void	affiche(t_data *data, int i)
{
	int	new_x;
	int	new_y;

	new_x = data->player_x;
	new_y = data->player_y;
	if (i == 1)
		new_x -= TILE_SIZE;
	if (i == 2)
		new_x += TILE_SIZE;
	if (i == 3)
		new_y -= TILE_SIZE;
	if (i == 4)
		new_y += TILE_SIZE;
	data->moves++;
	my_test_func(data, new_x, new_y);
}
