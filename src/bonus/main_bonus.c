/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:02:47 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/10 14:21:56 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	start_section(t_section *section)
{
	section->width = WIDTH;
	section->height = HEIGHT;
	section->column = 0;
	section->row = 0;
	section->map = NULL;
	section->diff_x = 0;
	section->diff_y = 0;
	section->zoom = 1;
	section->persp = 0.5236;
	section->angle = 0.7854;
	section->is_isometric = 1;
}

static void	start_menu(t_section *section)
{
	mlx_string_put(section->mlx, section->win, 10, 10 + 10, 0xFFFFFF,
		"Move with: AWSD");
	mlx_string_put(section->mlx, section->win, 10, 20 + 10 + 5, 0xFFFFFF,
		"Rotate with: QR");
	mlx_string_put(section->mlx, section->win, 10, 35 + 10 + 5, 0xFFFFFF,
		"Zoom with: +-");
	mlx_string_put(section->mlx, section->win, 10, 50 + 10 + 5, 0xFFFFFF,
		"Persp with: P");
}

void	clear_screen(t_section *section)
{
	int	index_x;
	int	index_y;

	index_x = 0;
	index_y = 0;
	while (index_x <= section->width)
	{
		while (index_y <= section->height)
		{
			ft_draw_pixel(section, index_x, index_y, 0x000000);
			index_y++;
		}
		index_y = 0;
		index_x++;
	}
	mlx_put_image_to_window(section->mlx, section->win, section->data->img, 0,
		0);
}

void	print_screen(t_section *section)
{
	clear_screen(section);
	ft_draw_map(section);
	mlx_put_image_to_window(section->mlx, section->win, section->data->img, 0,
		0);
	start_menu(section);
}

int	main(int ac, char **av)
{
	t_section	section;
	t_data		data;

	if (ac != 2)
		exit(-1);
	section.mlx = mlx_init();
	start_section(&section);
	mlx_get_screen_size(section.mlx, &section.width, &section.height);
	section.win = mlx_new_window(section.mlx, section.width, section.height,
			"fdf");
	data.img = mlx_new_image(section.mlx, section.width, section.height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	section.data = &data;
	get_all_map(av[1], &section);
	section.per_pixel = (section.height / section.row) * .75;
	print_screen(&section);
	mlx_hook(section.win, 17, 0, ft_close, &section);
	mlx_hook(section.win, 3, 1L << 1, ft_handle_key_up, &section);
	mlx_loop(section.mlx);
}
