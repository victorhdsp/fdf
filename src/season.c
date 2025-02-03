/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   season.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:44:30 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/03 08:52:41 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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