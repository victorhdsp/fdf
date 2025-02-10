/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:02:47 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/10 14:21:27 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	start_section(t_section *section)
{
	section->mlx = NULL;
	section->win = NULL;
	section->data = NULL;
	section->width = WIDTH;
	section->height = HEIGHT;
	section->per_pixel = 0;
	section->column = 0;
	section->row = 0;
	section->map = NULL;
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
}

static int	ft_handle_key(int keycode, t_section *section)
{
	if (keycode == 65307)
		ft_close(section);
	return (0);
}

int	main(int ac, char **av)
{
	t_section	section;
	t_data		data;

	if (ac != 2)
		exit(-1);
	start_section(&section);
	section.mlx = mlx_init();
	if (!section.mlx)
		ft_close(&section);
	mlx_get_screen_size(section.mlx, &section.width, &section.height);
	section.win = mlx_new_window(section.mlx, section.width, section.height,
			"fdf");
	if (!section.win)
		ft_close(&section);
	data.img = mlx_new_image(section.mlx, section.width, section.height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	section.data = &data;
	get_all_map(av[1], &section);
	section.per_pixel = (section.height / section.row) * .75;
	print_screen(&section);
	mlx_hook(section.win, 17, 0, ft_close, &section);
	mlx_hook(section.win, 2, 1L << 0, ft_handle_key, &section);
	mlx_loop(section.mlx);
}
