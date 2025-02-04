/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:36:00 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/04 08:55:43 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_centralize(double *x, double *y, double z, t_season *season)
{
	double	div_x;
	double	div_y;

	div_x = ((season->column - season->row) * cos(0.523599));
	div_y = ((season->column + season->row) * sin(0.523599) - z);
	*x = (WIDTH / 2) - ((div_x * season->per_pixel) / 2);
	*y = (HEIGHT / 2) - ((div_y * season->per_pixel) / 2);
}

t_pixel_source	*ft_distort_pixel(int x, int y, t_season *season)
{
	int		index;
	double	inner_z;
	double	inner_x;
	double	inner_y;

	index = x + (y * (season->column + 1));
	inner_z = ((season->map[index].z * season->column) / season->column)
		* season->zoom;
	ft_centralize(&inner_x, &inner_y, inner_z, season);
	inner_x += ((x - y) * cos(0.523599)) * season->per_pixel;
	inner_y += ((x + y) * sin(0.523599) - inner_z) * season->per_pixel;
	return (ft_create_pixel_source(inner_x, inner_y, season->map[index].color));
}
