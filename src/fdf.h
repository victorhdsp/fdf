/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:36:13 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/03 08:52:33 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define boolean int
# define false 0
# define true 1
# define WIDTH 1000
# define HEIGHT 1000

# include "../minilibx-linux/mlx.h"
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct  s_pixel_source {
    double     x;
    double     y;
    int     color;
}               t_pixel_source;

typedef struct	s_map_position
{
	int		z;
	int		color;
	boolean	skip;
}				t_map_position;

typedef struct s_season
{
	double	per_pixel;
	int		column;
	int		row;
	int		screen_x;
	int		screen_y;
	t_map_position  *map;
}				t_season;

void    ft_draw_pixel(t_data *data, int x, int y, int color);
t_pixel_source  *ft_create_pixel_source(int x, int y, int color);
void    ft_draw_line(t_data *data, t_pixel_source *px1, t_pixel_source *px2);
void	get_all_map(char *path, t_season *season);
int		ft_htoi(char *value);
char	*ft_join_with_space(char *s1, char *s2);
void    ft_draw_map(t_data *data, t_season *season);
t_pixel_source *ft_distort_pixel(int x, int y, t_season *season);

#endif