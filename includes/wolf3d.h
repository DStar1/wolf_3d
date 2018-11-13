/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 00:26:23 by hasmith           #+#    #+#             */
/*   Updated: 2018/11/12 17:49:06 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "../minilibx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <assert.h>

# define USAGE "wolf3d -> Usage:\n./wolf3d [map]\n"
# define MAP_ERROR "Invalid Map!\n"


///////////////// COLORS
#define RGB_Red 0xFF0000  //red
#define RGB_Green 0x008000  //green
#define RGB_Blue 0x0000FF   //blue
#define RGB_White 0xFFFFFF  //white
#define RGB_Yellow 0xFFFF00 //yellow
#define RGB_GREY 0xA9A9A9 //grey






typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct		s_point_int
{
	int				x;
	int				y;
}					t_point_int;

typedef struct		s_map
{
	int				height;
	int				width;
	char			**map;
	t_point			start;
}					t_map;

typedef struct		s_player
{
	t_point			position;
	t_point			direction;
	t_point			plane;
}					t_player;

typedef struct		s_raycast
{
	t_point			pos; //start position for ray
	t_point_int		map; //which coordinate are we in?
	t_point			direction; //initial direction vector
	t_point			plane; //camera plane
	t_point			ray; //ray direction
	t_point			delta_dist; //length of ray on both axis
	t_point			side_dist; 
	t_point_int		step; //direction to step in?
	double			perp_wall_dist;
	double			camera_x;
	int				hit; //did we hit a wall?
	int				side;

    double			moveSpeed;
    double			rotSpeed;
	double			frameTime;
  	double 			time;
  	double 			oldTime;
}					t_raycast;

// typedef	struct		s_thread
// {
// 	t_wolf	*m;
// 	int		count;
// }					t_thread;

typedef struct		s_mlx
{
	char			*img_int;
	void			*mlx_ptr;
	void			*img_ptr;
	int				bpp;
	int				size_line;
	int				endian;
	void			*mlx;
	void			*win;
	int				im_buff_size;

	int				exit;
	int				space;
	int				wsize;
	int				height;
	int				width;
	int				mouse_x;
	int				mouse_y;

	int				theme;

	//change to master struct//
	t_map			*map;
	t_raycast 		*r;
	/////////////////////////
}					t_mlx;

// Later impliment for master struct
typedef	struct		s_wolf
{
	t_mlx	*mlx;
	t_map	*map;
	t_raycast *r;

}					t_wolf;

t_map			*read_validate_map(char *filename);

void			ft_print_strings(char **strings);
char			**strsplit(char *str);
char			*replace_char(char *s, int old, int new_);
int				ptr_count(char **s);
void			set_hooks(t_wolf *m);
void			start(t_wolf *m, t_map *map);
int 			verLine(int x, int y1, int y2, int color, t_wolf *m);
void			init_raycast_vars(t_wolf *m, t_raycast *r);
void			move_forward(t_wolf *m);
void			move_back(t_wolf *m);
void			move_left(t_wolf *m);
void			move_right(t_wolf *m);
int				key_press_hook(int keycode, t_wolf *mast);
void			create_image(t_wolf *m);
void	pixel_str(t_wolf *m);

#endif 
