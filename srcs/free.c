/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:30:25 by mchiacha          #+#    #+#             */
/*   Updated: 2025/12/08 17:59:55 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_map(char **map, int rows)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_images(t_data *data)
{
	int	i;

	if (!data || !data->mlx_ptr)
		return ;
	if (data->background)
		mlx_destroy_image(data->mlx_ptr, data->background);
	if (data->wall)
		mlx_destroy_image(data->mlx_ptr, data->wall);
	if (data->exit_close)
		mlx_destroy_image(data->mlx_ptr, data->exit_close);
	if (data->exit_open)
		mlx_destroy_image(data->mlx_ptr, data->exit_open);
	if (data->treasure)
		mlx_destroy_image(data->mlx_ptr, data->treasure);
	if (data->floor)
		mlx_destroy_image(data->mlx_ptr, data->floor);
	i = 0;
	while (i < 7)
	{
		if (data->butterfly[i])
			mlx_destroy_image(data->mlx_ptr, data->butterfly[i]);
		i++;
	}
}

void	my_little_free(t_data *data)
{
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		data->mlx_ptr = NULL;
	}
}

void	clean_and_exit(t_data *data, const char *msg)
{
	size_t	len;

	if (msg)
	{
		len = ft_strlen(msg);
		write(1, msg, len);
	}
	if (data)
	{
		if (data->map)
			free_map(data->map, data->rows);
		free_images(data);
		if (data->win_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		if (data->mlx_ptr)
		{
			mlx_destroy_display(data->mlx_ptr);
			free(data->mlx_ptr);
		}
		ft_memset(data, 0, sizeof(t_data));
	}
	if (msg && ft_strncmp(msg, "Error\n", 6) == 0)
		exit(1);
	else
		exit(0);
}
