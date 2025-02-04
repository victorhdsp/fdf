/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:02:47 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/04 08:54:21 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_screen(void *mlx, void *mlx_win, t_data *data, t_season *season)
{
	ft_draw_map(data, season);
	mlx_put_image_to_window(mlx, mlx_win, (*data).img, 0, 0);
	mlx_loop(mlx);
}

int	main(int ac, char **av)
{
	void		*mlx;
	void		*mlx_win;
	t_data		data;
	t_season	season;

	if (ac != 2)
		exit(-1);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Hello world!");
	data.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	season.diff_x = 0;
	season.diff_y = 0;
	season.zoom = 1;
	get_all_map(av[1], &season);
	season.per_pixel = ((WIDTH / season.column) / 2);
	print_screen(mlx, mlx_win, &data, &season);
}
