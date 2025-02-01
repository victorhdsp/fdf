/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:36:00 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/01 10:55:04 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pixel_source  *ft_create_pixel_source(int x, int y, int color)
{
    t_pixel_source *s_pixel;

	s_pixel = malloc(1 * sizeof(t_pixel_source));
	s_pixel->x = x;
	s_pixel->y = y;
	s_pixel->color = color;
    return (s_pixel);
}

static int  ft_create_color(int hex_ini, int hex_end, int step, int index)
{
    double r;
    double g;
    double b;

    r = ((((hex_ini >> 16) & 0xFF) - ((hex_end >> 16) & 0xFF))) / step;
    g = (((hex_ini >> 8) & 0xFF) - ((hex_end >> 8) & 0xFF)) / step;
    b = ((hex_ini & 0xFF) - (hex_end & 0xFF)) / step;
    r = ((hex_ini >> 16) & 0xFF) + (r * index);
    g = ((hex_ini >> 8) & 0xFF) + (g * index);
    b = (hex_ini & 0xFF) + (b * index);
    return((abs(r) << 16) + (abs(g) << 8) + abs(b));
}

void	ft_draw_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    ft_draw_line(t_data *data, t_pixel_source *px_ini, t_pixel_source *px_end)
{
    double delta_x;
    double delta_y;
    int color;
    int index;
    int step;

    delta_x = px_end->x - px_ini->x;
    delta_y = px_end->y - px_ini->y;
    if (fabs(delta_x) >= fabs(delta_y))
        step = fabs(delta_x);
    else
        step = fabs(delta_y);
    delta_x = delta_x / step;
    delta_y = delta_y / step;
    index = 0;
    while (index < step)
    {
        color = ft_create_color(px_ini->color, px_end->color, step, index);
        ft_draw_pixel(data, px_ini->x, px_ini->y, color);
        px_ini->x += delta_x;
        px_ini->y += delta_y;
        index++;
    }
}
