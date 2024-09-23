/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhamass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:29:19 by akhamass          #+#    #+#             */
/*   Updated: 2024/09/01 19:29:20 by akhamass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	map_checker(t_data *data)
{
	int	i;

	if (!(ft_check_line(data->map[0], data->content.wall)))
		return (ft_free_map2(data) && 0);
	i = 1;
	while (data->map[i] != NULL)
	{
		if (!(ft_check_col(data->map[i], data->content.wall, data)))
			return (ft_free_map2(data) && 0);
		else if (!(ft_check_other(data->map[i], &(data->content))))
			return (ft_free_map2(data) && 0);
		i++;
	}
	data->height = i;
	if (!(ft_check_line(data->map[i - 1], data->content.wall)))
		return (ft_free_map2(data) && 0);
	return (1);
}

int	check_map_size(char **map)
{
	int	map_height;
	int	map_width;
	int	i;

	map_height = 0;
	while (map[map_height])
		map_height++;
	i = 0;
	while (map[i])
	{
		map_width = ft_strlen(map[i]);
		if (map_width > MAX_MAP_WIDTH)
		{
			ft_error_so_long("Error\nMap width exceeds maximum allowed\n");
			return (0);
		}
		i++;
	}
	if (map_height > MAX_MAP_HEIGHT)
	{
		ft_error_so_long("Error\nMap height exceeds maximum allowed\n");
		return (0);
	}
	return (1);
}

void	init_data(t_data *data)
{
	data->img.img_wall = NULL;
	data->img.img_floor = NULL;
	data->img.img_collect = NULL;
	data->img.img_player = NULL;
	data->img.img_exit = NULL;
	data->mlx_ptr = NULL;
	data->mlx_win = NULL;
}
