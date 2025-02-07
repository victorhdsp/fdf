/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:44:30 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/05 20:28:16 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_draw_chuck(t_section *section, int x, int y)
{
	t_pixel_source	px1;
	t_pixel_source	px2;

	if (x > 0)
	{
		px1 = ft_distort_pixel((x - 1), y, section);
		px2 = ft_distort_pixel(x, y, section);
		ft_draw_line(section, &px1, &px2);
	}
	if (y > 0)
	{
		px1 = ft_distort_pixel(x, (y - 1), section);
		px2 = ft_distort_pixel(x, y, section);
		ft_draw_line(section, &px1, &px2);
	}
}

void	ft_draw_map(t_section *section)
{
	int	x;
	int	y;
	int	index;

	x = 0;
	y = 0;
	index = 0;
	while (index != (section->column + 1) * section->row)
	{
		if (section->map[index].skip == FALSE)
			ft_draw_chuck(section, x, y);
		else
		{
			y++;
			x = -1;
		}
		x++;
		index = x + (y * (section->column + 1));
	}
}
