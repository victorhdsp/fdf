/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:44:30 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/05 16:50:37 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*get_all_map_string(char *path)
{
	char	*result;
	char	*tmp;
	char	*tmp2;
	int		fd;

	fd = open(path, O_RDONLY);
	tmp = get_next_line(fd);
	result = NULL;
	while (tmp)
	{
		tmp2 = result;
		result = ft_join_with_space(tmp2, tmp);
		free(tmp);
		tmp = get_next_line(fd);
		free(tmp2);
	}
	free(tmp);
	return (result);
}

static t_map_position	get_map_item(char *item)
{
	t_map_position	map;
	char			*color;

	map.skip = FALSE;
	map.color = 0xF1F1F1;
	if (!ft_strncmp(item, "\n", 1))
	{
		map.skip = TRUE;
		return (map);
	}
	map.z = ft_atoi(item);
	color = ft_memchr(item, ',', ft_strlen(item));
	if (color && color[0])
		map.color = ft_htoi(color + 1);
	return (map);
}

static void	ft_clear_splited_map(char **arr)
{
	int	index;

	index = 0;
	while (arr[index])
	{
		free(arr[index]);
		index++;
	}
	free(arr);
}

static void	ft_split_space_map(char *string_map, t_section *section,
		int map_index)
{
	char	**splited_by_space;
	int		index;

	index = 0;
	splited_by_space = ft_split(string_map, ' ');
	while (splited_by_space[index])
	{
		section->map[map_index + index] = get_map_item(splited_by_space[index]);
		index++;
	}
	section->column = index;
	ft_clear_splited_map(splited_by_space);
}

void	get_all_map(char *path, t_section *section)
{
	char	*string_map;
	int		index;
	char	**splited_by_break;

	index = 0;
	string_map = get_all_map_string(path);
	splited_by_break = ft_split(string_map, '\n');
	while (splited_by_break[index])
		index++;
	section->map = ft_calloc((index + 1) * index, sizeof(t_map_position));
	section->row = index;
	index = 0;
	while (splited_by_break[index])
	{
		ft_split_space_map(splited_by_break[index], section, (section->column + 1)
			* index);
		index++;
		section->map[((section->column + 1) * index) - 1] = get_map_item("\n");
	}
	ft_clear_splited_map(splited_by_break);
	free(string_map);
}
