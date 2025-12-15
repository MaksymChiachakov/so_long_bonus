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

// int handle_keyrelease(int keysym, void *param)
// {
//     t_data *data = (t_data *)param;

//     if (keysym == XK_w || keysym == XK_a ||
//         keysym == XK_s || keysym == XK_d ||
//         keysym == XK_Up || keysym == XK_Down ||
//         keysym == XK_Left || keysym == XK_Right)
//     {
// 		if (keysym == XK_a || keysym == XK_A || keysym == XK_Left)
// 			affiche(data, 1);
// 		if (keysym == XK_d || keysym == XK_D || keysym == XK_Right)
// 			affiche(data, 2);
// 		if (keysym == XK_w || keysym == XK_W || keysym == XK_Up)
// 			affiche(data, 3);
// 		if (keysym == XK_s || keysym == XK_S || keysym == XK_Down)
// 			affiche(data, 4);
//         data->is_moving = 0;
//         data->frame = 0;

//         my_new_best_func(data);
//         put_image_with_transparency(data,
//             data->player_img[0],
//             data->offset_x + data->player_x,
//             data->offset_y + data->player_y);
//     }
//     return (0);
// }


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
	ft_printf("Moves: %d\n", data->moves++);
	my_test_func(data, new_x, new_y);
}
