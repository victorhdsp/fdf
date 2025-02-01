/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:02:47 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/01 12:39:17 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_screen(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 600, 600, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	
	ft_draw_line(&img, ft_create_pixel_source(0, 0, 0x00FF0000), ft_create_pixel_source(500, 150, 0x00FF0000));
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

int	main(int ac, char **av)
{
	void	*mlx;
	void	*mlx_win;
	t_data	data;
	t_season		season;

	if (ac != 2)
		exit(-1);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Hello world!");
	data.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	season.column = -1;
	season.row = -1;
	get_all_map(av[1], &season);
	season.screen_x = WIDTH;
	season.screen_y = HEIGHT;
	season.per_pixel = (HEIGHT / 6) / (season.column - 1); 
	ft_draw_map(&data, &season);

	//test_ft_draw_line(&data, 50, 50, 100, 30, 0xFFFFFF);

	mlx_put_image_to_window(mlx, mlx_win, data.img, 0, 0);
	mlx_loop(mlx);
}
