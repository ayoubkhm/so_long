/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhamass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:29:52 by akhamass          #+#    #+#             */
/*   Updated: 2024/09/09 20:56:03 by akhamass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	find_player_position(t_data *data)
{
	int	y;
	int	x;

	if (data->map == NULL)
	{
		printf("Error: Map not loaded.\n");
		return (0);
	}
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (data->map[y][x] == 'P')
			{
				data->pos.x = x;
				data->pos.y = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	dfs_explore(t_dfs *dfs, int x, int y)
{
	int	pos;

	pos = y * dfs->map_width + x;
	if (x < 0 || y < 0 || x >= dfs->map_width || y >= dfs->map_height
		|| dfs->map[y][x] == '\n' || dfs->map[y][x] == '1'
		|| dfs->visited[y][x])
		return ;
	dfs->visited[y][x] = 1;
	if (dfs->map[y][x] == 'C')
	{
		dfs->path_items++;
	}
	if (dfs->map[y][x] == 'E')
	{
		dfs->path_exit++;
		return ;
	}
	dfs_explore(dfs, x + 1, y);
	dfs_explore(dfs, x - 1, y);
	dfs_explore(dfs, x, y + 1);
	dfs_explore(dfs, x, y - 1);
}

void	free_visited(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

int	init_dfs(t_dfs *dfs, t_data *data)
{
	int	i;

	dfs->map = data->map;
	dfs->map_width = data->width;
	dfs->map_height = data->height;
	dfs->path_exit = 0;
	dfs->path_items = 0;
	dfs->visited = malloc(sizeof(int *) * dfs->map_height);
	if (dfs->visited == NULL)
		return (0);
	i = 0;
	while (i < dfs->map_height)
	{
		dfs->visited[i] = malloc(sizeof(int) * dfs->map_width);
		if (dfs->visited[i] == NULL)
		{
			while (--i >= 0)
				free(dfs->visited[i]);
			free(dfs->visited);
			return (0);
		}
		memset(dfs->visited[i], 0, sizeof(int) * dfs->map_width);
		i++;
	}
	return (1);
}

int	verif_path(t_data *data)
{
	t_dfs	dfs;

	if (!init_dfs(&dfs, data))
		return (0);
	dfs_explore(&dfs, data->pos.x, data->pos.y);
	if (dfs.path_exit != 1 || data->content.count_c != dfs.path_items)
	{
		free_visited(dfs.visited, dfs.map_height);
		return (0);
	}
	free_visited(dfs.visited, dfs.map_height);
	return (1);
}
