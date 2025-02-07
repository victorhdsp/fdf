/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_up_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:32:32 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/07 11:01:28 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <X11/keysym.h>

int	ft_close(t_section *section)
{
	mlx_destroy_image(section->mlx, section->data->img);
	mlx_destroy_window(section->mlx, section->win);
	mlx_destroy_display(section->mlx);
	free(section->map);
	free(section->mlx);
	exit(0);
}

static int	ft_zoom(t_section *section, double value)
{
	section->zoom += value;
	if (section->zoom <= 0.1)
		section->zoom = 0.1;
	print_screen(section);
	return (1);
}

static int	ft_translate(t_section *section, int x, int y)
{
	section->diff_x += x;
	section->diff_y += y;
	print_screen(section);
	return (1);
}

static int	ft_rotate(t_section *section, double angle)
{
	section->angle += angle;
	if (section->angle <= 0)
		section->angle = 0;
	if (section->angle >= 0.523599)
		section->angle = 0.523599;
	print_screen(section);
	return (1);
}

int	ft_handle_key_up(int keycode, t_section *section)
{
	if (keycode == XK_Escape)
		ft_close(section);
	if (keycode == XK_KP_Subtract || keycode == XK_minus)
		ft_zoom(section, -.05);
	if (keycode == XK_KP_Add || keycode == XK_plus)
		ft_zoom(section, .05);
	if (keycode == XK_Left || keycode == XK_a)
		ft_translate(section, -10, 0);
	if (keycode == XK_Right || keycode == XK_d)
		ft_translate(section, 10, 0);
	if (keycode == XK_Up || keycode == XK_w)
		ft_translate(section, 0, -10);
	if (keycode == XK_Down || keycode == XK_s)
		ft_translate(section, 0, 10);
	if (keycode == XK_KP_Divide || keycode == XK_q)
		ft_rotate(section, -.1);
	if (keycode == XK_KP_Multiply || keycode == XK_e)
		ft_rotate(section, .1);
	return (0);
}
