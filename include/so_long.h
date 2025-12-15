/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:34:03 by mchiacha          #+#    #+#             */
/*   Updated: 2025/12/15 10:37:46 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# ifndef _GNU_SOURCE
#  define _GNU_SOURCE 
# endif
# define WINDOW_WIDTH 1900
# define WINDOW_HEIGHT 1000
# define TILE_SIZE 64
# define MLX_ERROR 1

# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include "../Libft/libft.h"

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*background;
	void	*wall;
	void	*exit_close;
	void	*exit_open;
	void	*treasure;
	void	*floor;
	void	*butterfly[7];
	int		frame;
	int		player_x;
	int		player_y;
	int		offset_x;
	int		offset_y;
	int		player_w;
	int		player_h;
	char	**map;
	int		rows;
	int		cols;
	int		collectibles;
	int		moves;
}	t_data;

typedef struct s_imginfo
{
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_imginfo;

typedef struct s_rc
{
	int		rows;
	int		cols;
	char	**copy;
}	t_rc;

typedef struct s_pt
{
	int	x;
	int	y;
}	t_pt;

typedef struct s_size
{
	int	rows;
	int	cols;
}	t_size;

int		flood_check(t_data *data);
void	render_map2(t_data *d, int x, int y);
void	free_map(char **map, int rows);
void	free_images(t_data *data);
void	clean_and_exit(t_data *data, const char *msg);
void	my_best_func(char c, t_data *data, int px, int py);
void	load_butterfly(t_data *data);
int		animation_loop(t_data *d);
void	finish_game(t_data *data);
void	pixel_to_tile(int px, int py, int *tx, int *ty);
int		handle_keypress(int keysym, void *param);
int		handle_close(void *param);
int		has_extension_ber(const char *name);
int		validate_map_structure(t_data *data, char **map, char **err_msg);
char	**read_map(const char *filename, int *rows, int *cols);
void	center_map(t_data *data);
void	render_background(t_data *data);
void	render_map(t_data *data);
char	*ft_strjoin(char *s1, char *s2);
int		ft_is_new_line(char *str);
char	*ft_get_line(char *str);
char	*ft_next(char *str);
char	*get_next_line(int fd);
int		flood_check(t_data *data);
void	bfs_run(char **copy, t_pt *queue, int rows, int cols);
int		put_image_with_transparency(t_data *data, void *img, int x, int y);
void	init_player(t_data *data);
int		flood_verify(char **copy, char **map, int rows, int cols);
char	**copy_map(char **map, int rows);
int		find_player(char **map, t_size size, int *sx, int *sy);
void	set_neighbor(t_pt cur, int dir, int *nx, int *ny);
void	process_neighbors(t_rc rc, t_pt cur, t_pt *queue, int *tail);
char	**my_free(char *row_line, char **map, int fd, int r);
char	**my_new_func(char **map, char *row, int r);
void	my_new_best_func(t_data *data);
void	my_test_second_func(t_data *data, int keysym);
void	affiche(t_data *data, int i);
void	my_test_func(t_data *data, int new_x, int new_y);

#endif
