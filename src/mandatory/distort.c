/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:36:00 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/10 08:15:05 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	ft_per_pixel(double value, t_section *section)
{
	return (value * section->per_pixel * 1);
}

void	ft_centralize(double *x, double *y, double z, t_section *section)
{
	double	div_x;
	double	div_y;
	double	tmp;

	tmp = ((section->column - 1) * cos(0.7854)) - ((section->row - 1)
			* sin(0.7854));
	div_x = (tmp * cos(0.5236));
	tmp = ((section->column - 1) * sin(0.7854)) + ((section->row - 1)
			* cos(0.7854));
	div_y = (tmp * sin(0.5236) - z);
	*x = (section->width / 2) - (ft_per_pixel(div_x / 2, section));
	*y = (section->height / 2) - (ft_per_pixel(div_y / 2, section));
}

t_pixel_source	ft_distort_pixel(int x, int y, t_section *section)
{
	int		index;
	double	inner_z;
	double	inner_x;
	double	inner_y;
	double	tmp;

	index = x + (y * (section->column + 1));
	inner_z = section->map[index].z * .75;
	ft_centralize(&inner_x, &inner_y, inner_z, section);
	tmp = (x * cos(0.7854)) - (y * sin(0.7854));
	inner_x += ft_per_pixel(tmp * cos(0.5236), section);
	tmp = (x * sin(0.7854)) + (y * cos(0.7854));
	inner_y += ft_per_pixel(tmp * sin(0.5236) - inner_z, section);
	return (ft_create_pixel_source(inner_x, inner_y,
			section->map[index].color));
}
