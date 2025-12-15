/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:31:08 by mchiacha          #+#    #+#             */
/*   Updated: 2025/12/10 11:19:20 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	clean_line(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len && len <= 30 && line[len - 1] == '\n')
		line[--len] = '\0';
	return (len);
}

char	*validate_and_copy(char *line, int *width, char **map, int r)
{
	int		len;
	char	*row;

	(void)r;
	(void)map;
	len = clean_line(line);
	if (*width == -1)
		*width = len;
	else if (*width != len)
		return (NULL);
	row = malloc(len + 1);
	if (!row)
		return (NULL);
	ft_strlcpy(row, line, len + 1);
	return (row);
}

char	**append_row(char **map, char *row, int r, int fd)
{
	char	**tmp;

	tmp = my_new_func(map, row, r);
	if (!tmp)
		return (my_free(row, map, fd, r));
	return (tmp);
}

static int	read_loop(int fd, char ***map_p, int *r_p, int *width_p)
{
	char	*line;
	char	*row;
	char	**tmp;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line && i <= 16)
	{
		if (i > 15)
			return (my_free(line, *map_p, fd, *r_p), 0);
		row = validate_and_copy(line, width_p, *map_p, *r_p);
		if (!row)
			return (my_free(line, *map_p, fd, *r_p), 0);
		free(line);
		tmp = append_row(*map_p, row, *r_p, fd);
		if (!tmp)
			return (0);
		*map_p = tmp;
		(*r_p)++;
		line = get_next_line(fd);
		i++;
	}
	return (1);
}

char	**read_map(const char *filename, int *rows, int *cols)
{
	int		fd;
	int		width;
	int		r;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	width = -1;
	r = 0;
	map = NULL;
	if (!read_loop(fd, &map, &r, &width))
	{
		get_next_line(-1);
		close(fd);
		return (NULL);
	}
	close(fd);
	if (r == 0)
		return (NULL);
	*rows = r;
	*cols = width;
	return (map);
}
