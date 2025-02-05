/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:10:25 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/05 16:51:46 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_close(t_section *section)
{
	mlx_destroy_image(section->mlx, section->data->img);
	mlx_destroy_window(section->mlx, section->win);
	mlx_destroy_display(section->mlx);
	free(section->map);
	exit(0);
}
