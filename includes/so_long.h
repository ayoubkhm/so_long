/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhamass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:13:42 by akhamass          #+#    #+#             */
/*   Updated: 2024/09/09 20:50:27 by akhamass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define MAX_MAP_WIDTH 31
# define MAX_MAP_HEIGHT 17

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>

typedef struct img_s
{
	void	*img_floor;
	void	*img_player;
	void	*img_exit;
	void	*img_wall;
	void	*img_collect;
	int		height;
	int		width;
	char	*player;
	char	*floor;
	char	*wall;
	char	*collect;
	char	*exit;
}				t_img;

typedef struct cnt_s
{
	char	exit;
	char	collect;
	char	player;
	char	wall;
	char	space;
	int		count_p;
	int		count_e;
	int		count_c;
}				t_cnt;

typedef struct pos_s
{
	int		x;
	int		y;
}				t_pos;

typedef struct data_s
{
	void	*mlx_ptr;
	void	*mlx_win;
	int		width;
	int		height;
	char	**map;
	t_cnt	content;
	t_img	img;
	t_pos	pos;
	int		count;
}				t_data;

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_map
{
	int	**vis;
	int	w;
	int	h;
	int	sx;
	int	sy;
}	t_map;

typedef struct s_dfs
{
	char	**map;
	int		**visited;
	int		map_width;
	int		map_height;
	int		path_items;
	int		path_exit;
	int		start_x;
	int		start_y;
}	t_dfs;

/*texture.c*/
int			chk_collect(t_data *data);
void		free_map(char **map);
int			key_press(int keysym, t_data *data);
int			handle_map_processing(t_data *data);
int			main(int argc, char **argv);

/*utils.c*/
int			ft_same_char(char *str);
void		*ft_error_so_long(char *str);
void		destroy_images(t_data *data);
int			end(t_data *data);
char		*read_map(int fd);

/*map_checker.c*/
int			map_checker(t_data *data);
void		init_data(t_data *data);
int			check_map_size(char **map);

/*map_checker_utils.c*/
int			ft_check_col(char *map_line, char wall, t_data *data);
int			ft_check_line(char *map_line, char wall);
int			ft_check_empty_lines(char **map);
void		ft_check_content(t_data *data);
int			ft_check_format(char **map);

/*map.c*/
char		*get_map(int fd);
void		*ft_free_map2(t_data *data);
char		**parse_map(int fd, t_data *data);
char		**map_core(char **str, t_data *data);
int			ft_check_other(char *map_line, t_cnt *content);

/*render_mouv.c*/
void		render_top(t_data *data);
void		render_right(t_data *data);
void		render_left(t_data *data);
void		render_down(t_data *data);

/*render.c*/
void		render_background(t_data *data);
void		render_other(t_data *data);
int			render(t_data *data);
int			core_render(t_data *data);
void		print_img(t_data *data, void *img, int x, int y);

/*set.c*/
void		set_content(t_cnt *content);
void		init_img_paths(t_data *data);
int			load_images(t_data *data);
int			set_img(t_data *data);

/*dfs.c*/
int			find_player_position(t_data *data);
void		dfs_explore(t_dfs *dfs, int x, int y);
void		free_visited(int **visited, int height);
int			verif_path(t_data *data);

#endif
