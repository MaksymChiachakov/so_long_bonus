#include "../include/so_long.h"

static int	main_validate(t_data *data)
{
	char	*err_msg;

	if (!data->map)
	{
		write(1, "Error\nFailed to read map or map not rectangular ", 49);
		write(1, "or map is very big\n", 20);
		return (clean_and_exit(data, NULL), 0);
	}
	err_msg = NULL;
	if (!validate_map_structure(data, data->map, &err_msg))
	{
		(void)err_msg;
		write(1, "Error\nInvalid map\n", 19);
		return (clean_and_exit(data, NULL), 0);
	}
	if (!flood_check(data))
	{
		write(1, "Error\nMap is not solvable\n", 27);
		free_map(data->map, data->rows);
		return (clean_and_exit(data, NULL), 0);
	}
	return (1);
}

static int	main_init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		free_map(data->map, data->rows);
		return (clean_and_exit(data, NULL), 1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT, "so_long");
	if (!data->win_ptr)
	{
		free_map(data->map, data->rows);
		return (clean_and_exit(data, NULL), 1);
	}
	return (1);
}

static void	main_load_images(t_data *data)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	data->background = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/background.xpm", &w, &h);
	data->wall = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/wall.xpm",
			&w, &h);
	data->floor = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/floor.xpm",
			&w, &h);
	data->exit_close = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/exit_close.xpm", &w, &h);
	data->treasure = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/treasure.xpm", &w, &h);
	data->exit_open = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/exit_open.xpm", &w, &h);
	// data->player_img = mlx_xpm_file_to_image(data->mlx_ptr,
	// 		"./textures/player.xpm", &data->player_w, &data->player_h);
	if (!data->background || !data->wall || !data->floor || !data->exit_close
		|| !data->treasure || !data->exit_open)
		clean_and_exit(data, "Error\nFailed to load one or more images\n");
}

void	load_butterfly(t_data *data)
{
	int	w;
	int	h;
	int	i;

	w = 0;
	h = 0;
	data->butterfly[0] = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/player.xpm", &data->player_w, &data->player_h);
	data->butterfly[1] = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/player2.xpm", &w, &h);
	data->butterfly[2] = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/player3.xpm", &w, &h);
	data->butterfly[3] = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/player4.xpm", &w, &h);
	data->butterfly[4] = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/player5.xpm", &w, &h);
	data->butterfly[5] = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/player6.xpm", &w, &h);
	data->butterfly[6] = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/player7.xpm", &w, &h);
	i = -1;
	while (++i < 7)
	{
		if (!data->butterfly[i])
			clean_and_exit(data, "Error\nFailed to load butterfly images\n");
	}
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

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (write(1, "Error\nUsage: ./so_long map.ber\n", 32), 1);
	if (!has_extension_ber(argv[1]))
		return (write(1, "Error\nMap file must have .ber extension\n", 41), 1);
	
	ft_memset(&data, 0, sizeof(data));
	data.moves = 1;
	data.player_x = -1;
	data.player_y = -1;
	data.player_w = 0;
	data.player_h = 0;
	data.offset_x = 0;
	data.offset_y = 0;
	data.rows = 0;
	data.cols = 0;
	data.collectibles = 0;
	data.frame = 0;
	data.mlx_ptr = NULL;
	data.win_ptr = NULL;
	data.background = NULL;
	data.treasure = NULL;
	// data.player_img = NULL;
	data.exit_close = NULL;
	data.exit_open = NULL;
	data.map = NULL;
	data.floor = NULL;
	data.wall = NULL;

	t_imginfo test;
	test.addr = NULL;
	test.bpp = 0;
	test.endian = 0;
	test.size_line = 0;
	(void)test;

	t_pt test2;
	test2.x = 0;
	test2.y = 0;

	t_rc test3;
	test3.cols = 0;
	test3.rows = 0;
	test3.copy = NULL;

	t_size test4;
	test4.cols = 0;
	test4.rows = 0;
	(void)test2;
	(void)test3;
	(void)test4;

	int i = -1;
	while (++i <= 7)
	{
		data.butterfly[i] = NULL;
		write(1, "c", 1);
	}
	data.map = read_map(argv[1], &data.rows, &data.cols);
	if (!main_validate(&data))
		return (clean_and_exit(&data, NULL), 1);
	if (!main_init_mlx(&data))
		return (clean_and_exit(&data, "Error\nFailed to create window\n"), 1);
	init_player(&data);
	main_load_images(&data);
	load_butterfly(&data);
	center_map(&data);
	render_map(&data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0L, handle_close, &data);
	mlx_loop_hook(data.mlx_ptr, animation_loop, &data);
	mlx_loop(data.mlx_ptr);
	clean_and_exit(&data, NULL);
	return (0);
}