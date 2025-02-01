/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   season.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:44:30 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/01 12:49:28 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_pixel_source *ft_distort_pixel(int x, int y, t_season *season)
{
    int     index;
    float     inner_z;
    float     inner_x;
    float     inner_y;

    index = x + (y * (season->column + 1));
    inner_z = season->map[index].z * (season->per_pixel / season->column);
    inner_x = (season->screen_x/2) - (season->screen_x/4);
    inner_y = (season->screen_y/2) - (season->screen_y/4);
    inner_x += (x * season->per_pixel) + (y * 85);
    inner_y += (y * season->per_pixel) - (x * 15);
    if (inner_z != 0)
    {
        inner_x = inner_x + (inner_z * .66);
        inner_y = inner_y - (inner_z * .33);
    }
    return (ft_create_pixel_source(inner_x, inner_y, season->map[index].color));
}

static void ft_draw_chuck(t_data *data, t_season *season, int x, int y)
{
    t_pixel_source *px1;
    t_pixel_source *px2;
    
    if (x > 0)
    {
        px1 = ft_distort_pixel((x - 1), y, season);
        px2 = ft_distort_pixel(x, y, season);
        ft_draw_line(data, px1, px2);
        free(px1);
        free(px2);
    }
    if (y > 0)
    {
        px1 = ft_distort_pixel(x, (y - 1), season);
        px2 = ft_distort_pixel(x, y, season);
        ft_draw_line(data, px1, px2);
        free(px1);
        free(px2);
    }
}

void    ft_draw_map(t_data *data, t_season *season)
{
    int x;
    int y;
    int index;

    x = 0;
    y = 0;
    index = 0;
    while (index != (season->column + 1) * season->row)
    {
        if (season->map[index].skip == false)
            ft_draw_chuck(data, season, x, y);
        else
        {
            y++;
            x = -1;
        }
        x++;
        index = x + (y * (season->column + 1));
    }
    
}