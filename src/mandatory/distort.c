/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:36:00 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/05 17:23:51 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	ft_per_pixel(double value, t_section *section)
{
	return (value * section->per_pixel);
}

void	ft_centralize(double *x, double *y, double z, t_section *section)
{
	double	div_x;
	double	div_y;

	div_x = ((section->column - section->row) * cos(0.523599));
	div_y = ((section->column + section->row) * sin(0.523599) - z);
	*x = (section->width / 2) - ((ft_per_pixel(div_x, section)) / 2);
	*y = (section->height / 2) - (ft_per_pixel(div_y, section) / 2);
}

t_pixel_source	ft_distort_pixel(int x, int y, t_section *section)
{
	int		index;
	double	inner_z;
	double	inner_x;
	double	inner_y;

	index = x + (y * (section->column + 1));
	inner_z = ((section->map[index].z * section->column) / section->column);
	ft_centralize(&inner_x, &inner_y, inner_z, section);
	inner_x += ft_per_pixel((x - y) * cos(0.523599), section);
	inner_y += ft_per_pixel((x + y) * sin(0.523599) - inner_z, section);
	return (ft_create_pixel_source(inner_x, inner_y,
			section->map[index].color));
}
