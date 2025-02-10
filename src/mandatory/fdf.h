/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:36:13 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/10 13:53:19 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define BOOLEAN int
# define FALSE 0
# define TRUE 1
# define WIDTH 1000
# define HEIGHT 1000

# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct s_pixel_source
{
	double			x;
	double			y;
	int				color;
}					t_pixel_source;

typedef struct s_map_position
{
	int				z;
	int				color;
	BOOLEAN			skip;
}					t_map_position;

typedef struct s_section
{
	void			*mlx;
	void			*win;
	t_data			*data;
	int				width;
	int				height;
	double			per_pixel;
	int				column;
	int				row;
	t_map_position	*map;
}					t_section;

void				ft_draw_pixel(t_section *section, int x, int y, int color);
t_pixel_source		ft_create_pixel_source(int x, int y, int color);
void				ft_draw_line(t_section *section, t_pixel_source *px1,
						t_pixel_source *px2);
void				get_all_map(char *path, t_section *section);
int					ft_htoi(char *value);
char				*ft_join_with_space(char *s1, char *s2);
void				ft_draw_map(t_section *section);
t_pixel_source		ft_distort_pixel(int x, int y, t_section *section);
void				print_screen(t_section *section);
void				clear_screen(t_section *section);
int					ft_close(t_section *section);

#endif