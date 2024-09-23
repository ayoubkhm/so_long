/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhamass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:29:07 by akhamass          #+#    #+#             */
/*   Updated: 2024/09/09 20:51:41 by akhamass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	*get_map(int fd)
{
	char	*buff;

	buff = read_map(fd);
	if (buff && *buff != '\0')
		return (buff);
	free(buff);
	ft_error_so_long("Error\nWrong lecture map\n");
	return (NULL);
}

void	*ft_free_map2(t_data *data)
{
	int		i;

	i = 0;
	while (data->map[i] != NULL)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = NULL;
	return (0);
}

char	**parse_map(int fd, t_data *data)
{
	char	*map_content;	

	map_content = get_map(fd);
	if (!map_content)
		return (NULL);
	data->map = ft_split(map_content, '\n');
	free(map_content);
	if (data->map == NULL)
		return (NULL);
	if (!check_map_size(data->map))
		return (ft_free_map2(data));
	ft_check_content(data);
	if (!(ft_check_format(data->map)))
		return (ft_free_map2(data));
	if (!map_checker(data))
		return (NULL);
	return (data->map);
}

char	**map_core(char **str, t_data *data)
{
	int		fd;

	fd = 0;
	data->map = NULL;
	if (ft_strchr(str[1], ".ber") == 0)
		return (ft_error_so_long("Error\nCorrect format map not found\n"));
	else
	{
		fd = open(str[1], O_RDONLY);
		if (fd > 0)
			data->map = parse_map(fd, data);
		else
			return (ft_error_so_long("Error\nFailed to open file\n"));
		close(fd);
		if ((data->content.count_c == 0 || data->content.count_e != 1
				|| data->content.count_p != 1) && data->map != NULL)
		{
			ft_free_map2(data);
			return (ft_error_so_long(
					"Error\nNeed 1 Player/Exit and at least 1 Object\n"));
		}
	}
	return (data->map);
}

int	ft_check_other(char *map_line, t_cnt *content)
{
	int		i;

	i = 0;
	while (map_line[i])
	{
		if (content->count_e > 1 || content->count_p > 1)
		{
			ft_error_so_long("Error\nWrong number of player or exit\n");
			return (0);
		}
		if (map_line[i] != content->wall && map_line[i] != content->player
			&& map_line[i] != content->exit && map_line[i] != content->collect
			&& map_line[i] != content->space)
		{
			ft_error_so_long("Error\nUnknown symbol(s) in map\n");
			return (0);
		}
		i++;
	}
	return (1);
}
