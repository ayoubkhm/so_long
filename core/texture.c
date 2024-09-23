/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhamass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:01:36 by akhamass          #+#    #+#             */
/*   Updated: 2024/09/09 20:49:53 by akhamass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	chk_collect(t_data *data)
{
	int		i;
	int		y;
	int		count;

	i = 0;
	y = 0;
	count = 0;
	while (data->map[y])
	{
		while (data->map[y][i])
		{
			if (data->map[y][i] == data->content.collect)
				count++;
			i++;
		}
		i = 0;
		y++;
	}
	return (count);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map != NULL)
	{
		while (map[i] != NULL)
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

int	key_press(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		end(data);
	if (keysym == XK_w)
		render_top(data);
	if (keysym == XK_d)
		render_right(data);
	if (keysym == XK_a)
		render_left(data);
	if (keysym == XK_s)
		render_down(data);
	return (0);
}

int	handle_map_processing(t_data *data)
{
	if (data->map == NULL)
	{
		end(data);
		return (0);
	}
	data->height = 0;
	while (data->map[data->height] != NULL)
	{
		data->height++;
	}
	data->width = strlen(data->map[0]);
	if (!find_player_position(data) || !verif_path(data) || !set_img(data))
	{
		ft_error_so_long("Error\n Please check your map details\n");
		end(data);
		return (0);
	}
	return (core_render(data));
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_error_so_long("Error\nPlease give 1 arg.ber\n");
		return (0);
	}
	else
	{
		init_data(&data);
		data.count = 0;
		data.mlx_ptr = mlx_init();
		if (data.mlx_ptr == NULL)
			return (1);
		set_content(&(data.content));
		data.map = map_core(argv, &data);
		if (!handle_map_processing(&data))
			return (0);
	}
	return (1);
}
