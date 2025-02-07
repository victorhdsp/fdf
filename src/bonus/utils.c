/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:58:01 by vide-sou          #+#    #+#             */
/*   Updated: 2025/02/07 11:33:27 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	ft_htoi(char *value)
{
	static char	hex[16] = "0123456789ABCDEF";
	int			count;
	int			index;
	int			result;

	index = 0;
	count = 0;
	result = 0;
	while (value[index])
	{
		value[index] = ft_toupper(value[index]);
		index++;
	}
	index = 0;
	while (value && value[count])
	{
		while (hex[index] && value[count] != hex[index])
			index++;
		if (value[count] == hex[index])
			result = (result * 16) + index;
		count++;
		index = 0;
	}
	return (result);
}

char	*ft_join_with_space(char *s1, char *s2)
{
	char	*result;
	char	*tmp;

	if (s1 && s2 && s1[0] && s2[0])
	{
		tmp = ft_strjoin(s1, " ");
		result = ft_strjoin(tmp, s2);
		free(tmp);
	}
	else
		result = ft_strjoin(s1, s2);
	return (result);
}
