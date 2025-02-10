/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:36:00 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/10 16:25:37 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pixel_source	ft_create_pixel_source(int x, int y, int color)
{
	t_pixel_source	s_pixel;

	s_pixel.x = x;
	s_pixel.y = y;
	s_pixel.color = color;
	return (s_pixel);
}

static int	ft_create_color(int hex_ini, int hex_end, int step, int index)
{
	double	r;
	double	g;
	double	b;

	r = ((((hex_ini >> 16) & 0xFF) - ((hex_end >> 16) & 0xFF))) / step;
	g = (((hex_ini >> 8) & 0xFF) - ((hex_end >> 8) & 0xFF)) / step;
	b = ((hex_ini & 0xFF) - (hex_end & 0xFF)) / step;
	r = ((hex_ini >> 16) & 0xFF) - (r * index);
	g = ((hex_ini >> 8) & 0xFF) - (g * index);
	b = (hex_ini & 0xFF) - (b * index);
	return (((int)r << 16) + ((int)g << 8) + (int)b);
}

void	ft_draw_pixel(t_section *section, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= section->width || y >= section->height)
		return ;
	dst = section->data->addr + (y * section->data->line_length + x
			* (section->data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_line(t_section *section, t_pixel_source *px_ini,
		t_pixel_source *px_end)
{
	double	diff_x;
	double	diff_y;
	int		color;
	int		index;
	int		diff;

	diff_x = px_end->x - px_ini->x;
	diff_y = px_end->y - px_ini->y;
	if (fabs(diff_x) >= fabs(diff_y))
		diff = fabs(diff_x);
	else
		diff = fabs(diff_y);
	diff_x = diff_x / diff;
	diff_y = diff_y / diff;
	index = 0;
	while (index < diff)
	{
		color = ft_create_color(px_ini->color, px_end->color, diff, index);
		ft_draw_pixel(section, px_ini->x, px_ini->y, color);
		px_ini->x += diff_x;
		px_ini->y += diff_y;
		index++;
	}
}
