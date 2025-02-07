/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distort_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:36:00 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/07 15:24:53 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

double	ft_per_pixel(double value, t_section *section)
{
	return (value * section->per_pixel * section->zoom);
}

void	ft_centralize(double *x, double *y, double z, t_section *section)
{
	double	div_x;
	double	div_y;
	double	tmp;

	tmp = ((section->column - 1) * cos(section->angle)) - ((section->row - 1)
			* sin(section->angle));
	div_x = (tmp * cos(section->persp));
	tmp = ((section->column - 1) * sin(section->angle)) + ((section->row - 1)
			* cos(section->angle));
	div_y = (tmp * sin(section->persp) - z);
	*x = (section->width / 2) - (ft_per_pixel(div_x / 2, section));
	*y = (section->height / 2) - (ft_per_pixel(div_y / 2, section));
	*x += section->diff_x;
	*y += section->diff_y;
}

t_pixel_source	ft_distort_pixel(int x, int y, t_section *section)
{
	int		index;
	double	inner_z;
	double	inner_x;
	double	inner_y;
	double	tmp;

	index = x + (y * (section->column + 1));
	inner_z = section->map[index].z;
	ft_centralize(&inner_x, &inner_y, inner_z, section);
	tmp = (x * cos(section->angle)) - (y * sin(section->angle));
	inner_x += ft_per_pixel(tmp * cos(section->persp), section);
	tmp = (x * sin(section->angle)) + (y * cos(section->angle));
	inner_y += ft_per_pixel(tmp * sin(section->persp) - inner_z, section);
	return (ft_create_pixel_source(inner_x, inner_y,
			section->map[index].color));
}
