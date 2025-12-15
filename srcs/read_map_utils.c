/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:31:13 by mchiacha          #+#    #+#             */
/*   Updated: 2025/12/05 13:31:15 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	**my_free(char *row_line, char **map, int fd, int r)
{
	free(row_line);
	row_line = NULL;
	free_map(map, r);
	close(fd);
	return (NULL);
}

char	**my_new_func(char **map, char *row, int r)
{
	int		i;
	char	**tmp;

	tmp = malloc(sizeof(char *) * (r + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < r)
	{
		tmp[i] = map[i];
		i++;
	}
	tmp[r] = row;
	free(map);
	return (tmp);
}
