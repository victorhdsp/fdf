/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distort_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:36:00 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/08 11:42:47 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

double	ft_per_pixel(double value, t_section *section)
{
	return (value * section->per_pixel * section->zoom);
}

void	ft_isometric(t_section *section, double *x, double *y, double z)
{
	double	tmp;
	double	inner_x;
	double	inner_y;

	inner_x = *x;
	inner_y = *y;
	tmp = ((inner_x) * cos(section->angle)) - ((inner_y) * sin(section->angle));
	*x = ft_per_pixel(tmp * cos(section->persp), section);
	tmp = ((inner_x) * sin(section->angle)) + ((inner_y) * cos(section->angle));
	*y = ft_per_pixel(tmp * sin(section->persp) - z, section);
}

void	ft_conic(t_section *section, double *x, double *y, double z)
{
	double	tmp;
	double	inner_x;
	double	inner_y;
	double	dist;

	inner_x = *x;
	inner_y = *y;
	dist = 1.5;
	tmp = (((dist * inner_x) * cos(section->angle)) - ((dist * inner_y)
				* sin(section->angle))) / (z + dist);
	*x = ft_per_pixel(tmp * cos(section->persp), section);
	tmp = (((dist * inner_x) * sin(section->angle)) + ((dist * inner_y)
				* cos(section->angle))) / (z + dist);
	*y = ft_per_pixel(tmp * sin(section->persp) - z, section);
}

void	ft_centralize(double *x, double *y, double z, t_section *section)
{
	double	div_x;
	double	div_y;

	div_x = section->column - 1;
	div_y = section->row - 1;
	if (section->is_isometric)
		ft_isometric(section, &div_x, &div_y, z);
	else
		ft_conic(section, &div_x, &div_y, z);
	*x = (section->width / 2) - (div_x / 2);
	*y = (section->height / 2) - (div_y / 2);
	*x += section->diff_x;
	*y += section->diff_y;
}

t_pixel_source	ft_distort_pixel(int x, int y, t_section *section)
{
	double	inner_x;
	double	inner_y;
	double	outer_x;
	double	outer_y;
	int		index;

	index = x + (y * (section->column + 1));
	ft_centralize(&inner_x, &inner_y, section->map[index].z, section);
	outer_x = x;
	outer_y = y;
	if (section->is_isometric)
		ft_isometric(section, &outer_x, &outer_y, section->map[index].z);
	else
		ft_conic(section, &outer_x, &outer_y, section->map[index].z);
	inner_x += outer_x;
	inner_y += outer_y;
	return (ft_create_pixel_source(inner_x, inner_y,
			section->map[index].color));
}
