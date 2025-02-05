/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pan_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:10:25 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/05 16:36:17 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_down_pan(int button, int x, int y, t_section *section)
{
	if (button == 1)
	{
		section->hold_x = x;
		section->hold_y = y;
	}
	return (0);
}

int	ft_move_pan(int x, int y, t_section *section)
{
	int		diff_x;
	int		diff_y;

	diff_x = x - section->hold_x;
	diff_y = y - section->hold_y;	
	if (abs(diff_x) > 10 || abs(diff_y) > 10)
	{
		section->hold_x = x;
		section->hold_y = y;
		section->diff_x = diff_x;
		section->diff_y = diff_y;
		print_screen(section);
	}
	return (0);
}

int	ft_up_pan(int button, int x, int y, t_section *section)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		section->hold_x = -1;
		section->hold_y = -1;
	}
	return (0);
}