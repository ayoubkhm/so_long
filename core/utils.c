/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhamass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:01:43 by akhamass          #+#    #+#             */
/*   Updated: 2024/09/01 21:01:45 by akhamass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_same_char(char *str)
{
	int		i;
	char	buff;

	i = 0;
	buff = '1';
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] != buff && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	*ft_error_so_long(char *str)
{
	write(2, str, ft_strlen(str));
	return (0);
}

void	destroy_images(t_data *data)
{
	if (data->mlx_ptr)
	{
		if (data->img.img_wall)
			mlx_destroy_image(data->mlx_ptr, data->img.img_wall);
		if (data->img.img_floor)
			mlx_destroy_image(data->mlx_ptr, data->img.img_floor);
		if (data->img.img_collect)
			mlx_destroy_image(data->mlx_ptr, data->img.img_collect);
		if (data->img.img_player)
			mlx_destroy_image(data->mlx_ptr, data->img.img_player);
		if (data->img.img_exit)
			mlx_destroy_image(data->mlx_ptr, data->img.img_exit);
	}
}

int	end(t_data *data)
{
	if (data->map)
		free_map(data->map);
	destroy_images(data);
	if (data->mlx_win && data->mlx_ptr)
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(0);
}

char	*read_map(int fd)
{
	char	*buff;
	char	*line_map;
	char	*tmp_buff;
	int		char_count;

	buff = ft_strdup("");
	line_map = ft_strdup("");
	char_count = gnl(fd, &line_map);
	while (char_count > 0)
	{
		tmp_buff = buff;
		buff = ft_strjoin(buff, line_map);
		free(tmp_buff);
		free(line_map);
		line_map = ft_strdup("");
		char_count = gnl(fd, &line_map);
		tmp_buff = buff;
	}
	free(line_map);
	return (buff);
}
