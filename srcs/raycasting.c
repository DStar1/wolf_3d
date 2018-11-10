/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:34:04 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/09 21:26:38 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			init_raycast_vars(t_mlx *m, t_map *map, t_raycast *r)
{
	r->pos.x = map->start.x;
	r->pos.y = map->start.y;
	r->direction.x = 1;
	r->direction.y = 0;
	r->plane.x = 0;
	r->plane.y = 0.66;
}

void			configure_ray(t_raycast *r, t_mlx *m, int x)
{

	r->camera_x = 2 * x / (double)m->width - 1;
	r->ray.x = r->direction.x + r->plane.x * r->camera_x;
	r->ray.y = r->direction.y + r->plane.y * r->camera_x;
	r->map.x = (int)(floor(r->pos.x));
	r->map.y = (int)(floor(r->pos.y));
	r->delta_dist.x = ft_abs(1 / r->ray.x);
	r->delta_dist.y = ft_abs(1 / r->ray.y);
}

void			pre_dda(t_raycast *r)
{
	if (r->direction.x < 0)
	{
		r->step.x = -1;
		r->side_dist.x = (floor(r->pos.x) - r->map.x) * r->delta_dist.x;
	}
	else
	{
		r->step.x = 1;
		r->side_dist.x = (floor(r->map.x) + 1.0 - r->pos.x) * r->delta_dist.x;
	}
	if (r->direction.y < 0)
	{	
		r->step.y = -1;
		r->side_dist.y = floor((r->pos.y) - r->map.y) * r->delta_dist.y;
	}
	else
	{
		r->step.y = 1;	
		r->side_dist.y = (floor(r->map.y) + 1.0 - r->pos.y) * r->delta_dist.y;
	}
}

void			do_dda(t_raycast *r, t_map *map)
{
	r->hit = 0;
	while (!r->hit)
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta_dist.x;
			r->map.x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->side_dist.y += r->delta_dist.y;
			r->map.y += r->step.y;
			r->side = 1;
		}
		if (map->map[r->map.y][r->map.x] == '1')
		{
			printf("hit! -> map[%i][%i]\n", r->map.y, r->map.x);
			r->hit = 1;
		}
	}
}

void			wall_distance(t_raycast *r)
{
	r->perp_wall_dist = (r->side == 0) ?
	(r->map.x - r->pos.x + (1 - r->step.x) / 2) / r->ray.x :
	(r->map.y - r->pos.y + (1 - r->step.y) / 2) / r->ray.y;
}

void			configure_line(t_raycast *r, t_mlx *m, t_map *map, int x)
{
	int					line_height;
	int					draw_start;
	int					draw_end;
	int					color;

	line_height = (int)(m->height / r->perp_wall_dist);
	draw_start = -line_height / 2 + m->height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + m->height / 2;
	if (draw_end >= m->height)
		draw_end = m->height - 1;
	if (map->map[r->map.y][r->map.x] == '1')
		color = RGB_GREY;
	if (r->side)
		color += 58;
	verLine(x, draw_start, draw_end, color, m);
}

void			start(t_mlx *m, t_map *map){
	t_raycast			r;

	init_raycast_vars(m, map, &r);
	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame
	for(int x = 0; x < m->width; x++)
	{
		configure_ray(&r, m, x);

		r.hit = 0;
		pre_dda(&r);
		//perform DDA
		do_dda(&r, map);
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		wall_distance(&r);
		configure_line(&r, m, map, x);
	}
}
