/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:44:30 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/05 20:26:20 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_rows_map(char *path, t_section *section)
{
	int		fd;
	int		index;
	char	*line;

	index = 0;
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	while (line[index])
	{
		while (line[index] == ' ')
			index++;
		section->column++;
		while (line[index] && line[index] != ' ')
			index++;
	}
	while (line)
	{
		section->row++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

static t_map_position	get_map_item(const char *item)
{
	t_map_position	map;
	int				index;
	char			color[8];

	index = 0;
	map.skip = FALSE;
	map.color = 0xF1F1F1;
	ft_memset(color, 0, 8);
	if (!ft_strncmp(item, "\n", 1))
	{
		map.skip = TRUE;
		return (map);
	}
	map.z = ft_atoi(item);
	while (*item && *item >= '0' && *item <= '9')
		item++;
	if (*item == ',')
		ft_memmove(color, item + 1, 8);
	if (color[0])
		map.color = ft_htoi(color + 1);
	return (map);
}

static void	ft_split_space_map(char *line, t_section *section, int map_index)
{
	int	index;

	index = 0;
	while (*line)
	{
		while (*line == ' ')
			line++;
		section->map[map_index + index] = get_map_item(line);
		index++;
		while (*line && *line != ' ')
			line++;
	}
}

void	get_all_map(char *path, t_section *section)
{
	int		index;
	int		fd;
	char	*line_map;

	index = 0;
	get_rows_map(path, section);
	fd = open(path, O_RDONLY);
	line_map = get_next_line(fd);
	section->map = ft_calloc((section->column + 1) * section->row,
			sizeof(t_map_position));
	while (line_map)
	{
		ft_split_space_map(line_map, section, (section->column + 1) * index);
		index++;
		section->map[((section->column + 1) * index) - 1] = get_map_item("\n");
		free(line_map);
		line_map = get_next_line(fd);
	}
	free(line_map);
}
