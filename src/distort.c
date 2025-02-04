/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:36:00 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/04 18:21:23 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_centralize(double *x, double *y, double z, t_section *section)
{
	double	div_x;
	double	div_y;

	div_x = ((section->column - section->row) * cos(0.523599));
	div_y = ((section->column + section->row) * sin(0.523599) - z);
	*x = (section->width / 2) - ((div_x * section->per_pixel) / 2);
	*y = (section->height / 2) - ((div_y * section->per_pixel) / 2);
}

t_pixel_source	*ft_distort_pixel(int x, int y, t_section *section)
{
	int		index;
	double	inner_z;
	double	inner_x;
	double	inner_y;

	index = x + (y * (section->column + 1));
	inner_z = ((section->map[index].z * section->column) / section->column)
		* section->zoom;
	ft_centralize(&inner_x, &inner_y, inner_z, section);
	inner_x += ((x - y) * cos(0.523599)) * section->per_pixel;
	inner_y += ((x + y) * sin(0.523599) - inner_z) * section->per_pixel;
	return (ft_create_pixel_source(inner_x, inner_y, section->map[index].color));
}
