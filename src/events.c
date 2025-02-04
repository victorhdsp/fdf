/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:10:25 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/04 17:44:40 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_close(int keycode, t_section *section)
{
	(void) keycode;
	mlx_destroy_image(section->mlx, section->data->img);
	mlx_destroy_window(section->mlx, section->win);
	mlx_destroy_display(section->mlx);
	exit(0);
}