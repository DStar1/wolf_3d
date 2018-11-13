/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:34:04 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/12 16:57:55 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			print_r_struct(t_mlx *m)//t_raycast *r)
{
	if (!m->r)
		return ;
	printf("-------------------------------------------\n");
	printf("position = [%f][%f]\n", m->r->pos.y, m->r->pos.x);
	printf("map = [%d][%d]\n", m->r->map.y, m->r->map.x);
	printf("direction = [%f][%f]\n", m->r->direction.y, m->r->direction.x);
	printf("plane = [%f][%f]\n", m->r->plane.y, m->r->plane.x);
	printf("ray direction = [%f][%f]\n", m->r->ray.y, m->r->ray.x);
	printf("delta distance = [%f][%f]\n", m->r->delta_dist.y, m->r->delta_dist.x);
	printf("side distance = [%f][%f]\n", m->r->side_dist.y, m->r->side_dist.x);
	printf("step = [%d][%d]\n", m->r->step.y, m->r->step.x);
	printf("perp_wall_dist = %f\n", m->r->perp_wall_dist);
	printf("camera_x = %f\n", m->r->camera_x);
}

void			init_raycast_vars(t_mlx *m, t_map *map, t_raycast *r)
{
	m->r->pos.x = map->start.x;
	m->r->pos.y = map->start.y;
	m->r->direction.x = -1;
	m->r->direction.y = 0;
	m->r->plane.x = 0;
	m->r->plane.y = 0.66;
	m->r->time = 0; //time of current frame
	m->r->oldTime = 0; //time of previous frame
}

void			configure_ray(t_mlx *m, int x)//t_raycast *r, t_mlx *m, int x)
{

	m->r->camera_x = (double)(2.0 * x) / (double)m->width - 1;
	printf("camera = %f\n", m->r->camera_x);
	m->r->ray.x = m->r->direction.x + m->r->plane.x * m->r->camera_x;
	m->r->ray.y = m->r->direction.y + m->r->plane.y * m->r->camera_x;
	m->r->map.x = (int)(floor(m->r->pos.x));
	m->r->map.y = (int)(floor(m->r->pos.y));
	m->r->delta_dist.x = fabs(1 / m->r->ray.x);
	m->r->delta_dist.y = fabs(1 / m->r->ray.y);
}

void			pre_dda(t_mlx *m)//t_raycast *r)
{
	if (m->r->ray.x < 0)
	{
		m->r->step.x = -1;
		m->r->side_dist.x = ((m->r->pos.x) - m->r->map.x) * m->r->delta_dist.x;
	}
	else
	{
		m->r->step.x = 1;
		m->r->side_dist.x = ((m->r->map.x) + 1.0 - m->r->pos.x) * m->r->delta_dist.x;
	}
	if (m->r->ray.y < 0)
	{	
		m->r->step.y = -1;
		m->r->side_dist.y = ((m->r->pos.y) - m->r->map.y) * m->r->delta_dist.y;
	}
	else
	{
		m->r->step.y = 1;	
		m->r->side_dist.y = ((m->r->map.y) + 1.0 - m->r->pos.y) * m->r->delta_dist.y;
	}
}

void			do_dda(t_mlx *m, t_map *map)//t_raycast *r, t_map *map)
{
	m->r->hit = 0;
	while (!m->r->hit)
	{
	//	printf("r-Map = [%d][%d]\n", m->r->map.y, m->r->map.x);
		if (m->r->side_dist.x < m->r->side_dist.y)
		{
			m->r->side_dist.x += m->r->delta_dist.x;
			m->r->map.x += m->r->step.x;
			m->r->side = 0;
		}
		else
		{
			m->r->side_dist.y += m->r->delta_dist.y;
			m->r->map.y += m->r->step.y;
			m->r->side = 1;
		}
		if (m->r->map.y <= 6  && m->r->map.y >= 4)
		{
	//		print_r_struct(r);
		}
		if (m->map->map[m->r->map.y][m->r->map.x] == '1')
		{
			printf("hit! -> map[%i][%i]\n", m->r->map.y, m->r->map.x);
//			printf("camera = %f\n", m->r->camera_x);
//			print_r_struct(r);
			m->r->hit = 1;
		}
	}
}

void			wall_distance(t_mlx *m)//t_raycast *r)
{
	m->r->perp_wall_dist = (m->r->side == 0) ?
	(m->r->map.x - m->r->pos.x + (1 - m->r->step.x) / 2) / m->r->ray.x :
	(m->r->map.y - m->r->pos.y + (1 - m->r->step.y) / 2) / m->r->ray.y;
}

void			configure_line(t_mlx *m, t_map *map, int x)//t_raycast *r, t_mlx *m, t_map *map, int x)
{
	int					line_height;
	int					draw_start;
	int					draw_end;
	int					color;

	line_height = (int)(m->height / m->r->perp_wall_dist);
	draw_start = -line_height / 2 + m->height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + m->height / 2;
	if (draw_end >= m->height)
		draw_end = m->height - 1;
	if (m->map->map[m->r->map.y][m->r->map.x] == '1')
		color = RGB_GREY;
	if (m->r->side)
		color += 118;
	verLine(x, draw_start, draw_end, color, m);
}

void			start(t_mlx *m, t_map *map){
	// t_raycast			*r;
//	mlx_destroy_image(m->mlx, m->img_ptr);
//	pixel_str(m);
	ft_bzero(m->img_int, 1000 * 1000 * 4);
	// r = m->r;//round about way of master struct

	// r = malloc(sizeof(t_raycast));
	// init_raycast_vars(m, map, r);

	//assert(m->r);
	for(int x = 0; x < m->width; x++)
	{
		// assert(m->r);
		configure_ray(m, x);//configure_ray(r, m, x);

		m->r->hit = 0;
		pre_dda(m);//pre_dda(r);
		//perform DDA
		do_dda(m, map);//do_dda(r, map);
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		wall_distance(m);//wall_distance(r);
//		print_r_struct(&r);
		configure_line(m, map, x);//configure_line(r, m, map, x);
	}

    // //timing for input and FPS counter
    // m->r->oldTime = m->r->time;
    // m->r->time = getTicks();
    // m->r->frameTime = (m->r->time - m->r->oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    // printf("%f\n", 1.0 / m->r->frameTime); //FPS counter
    // // redraw();
    // // cls();

    //speed modifiers
    m->r->moveSpeed = .05; //the constant value is in squares/second
    m->r->rotSpeed = .05; //the constant value is in radians/second
    // //speed modifiers
    // m->r->moveSpeed = m->r->frameTime * 5.0; //the constant value is in squares/second
    // m->r->rotSpeed = m->r->frameTime * 3.0; //the constant value is in radians/second
	create_image(m);
}
