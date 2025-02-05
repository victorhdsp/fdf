/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:10:25 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/05 09:58:35 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_zoom(int keycode, int x, int y, t_section *section)
{
	(void)x;
	(void)y;
	if (keycode == 4)
		section->zoom += .1;
	else if (keycode == 5)
		section->zoom -= .1;
	print_screen(section);
	return (0);
}

int ft_mouse_action(int keycode, int x, int y, t_section *section)
{
	if (keycode == 4 || keycode == 5)
		ft_zoom(keycode, x, y, section);
	else if (keycode == 1)
		ft_down_pan(keycode, x, y, section);
	return (0);
}

int ft_mouse_up(int keycode, int x, int y, t_section *section)
{
	if (keycode == 1)
		ft_up_pan(keycode, x, y, section);
	return (0);
}

int ft_mouse_move(int x, int y, t_section *section)
{
	if (section->hold_x != -1 && section->hold_y != -1)
		ft_move_pan(x, y, section);
	return (0);
}
