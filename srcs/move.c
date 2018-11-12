/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 00:26:23 by hasmith           #+#    #+#             */
/*   Updated: 2018/11/12 12:23:06 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
	// m->r->pos.x = map->start.x;
	// m->r->pos.y = map->start.y;
	// m->r->direction.x = -1;
	// m->r->direction.y = 0;
	// m->r->plane.x = 0;
	// m->r->plane.y = 0.66;
void	move_forward(t_mlx *m)
{
    if(m->map->map[(int)(m->r->pos.x + m->r->direction.x * m->r->moveSpeed)][(int)(m->r->pos.y)] == '0') m->r->pos.x += m->r->direction.x * m->r->moveSpeed;
    if(m->map->map[(int)(m->r->pos.x)][(int)(m->r->pos.y + m->r->direction.y * m->r->moveSpeed)] == '0') m->r->pos.y += m->r->direction.y * m->r->moveSpeed;
}

void	move_back(t_mlx *m)
{
    if(m->map->map[(int)(m->r->pos.x - m->r->direction.x * m->r->moveSpeed)][(int)(m->r->pos.y)] == '0') m->r->pos.x -= m->r->direction.x * m->r->moveSpeed;
    if(m->map->map[(int)(m->r->pos.x)][(int)(m->r->pos.y - m->r->direction.y * m->r->moveSpeed)] == '0') m->r->pos.y -= m->r->direction.y * m->r->moveSpeed;
}

void	move_left(t_mlx *m)
{
    //both camera direction and camera plane must be rotated
    double oldDirX = m->r->direction.x;
    m->r->direction.x = m->r->direction.x * cos((m->r->rotSpeed)) - m->r->direction.y * sin((m->r->rotSpeed));
    m->r->direction.y = oldDirX * sin((m->r->rotSpeed)) + m->r->direction.y * cos((m->r->rotSpeed));
    double oldPlaneX = m->r->plane.x;
    m->r->plane.x = m->r->plane.x * cos((m->r->rotSpeed)) - m->r->plane.y * sin((m->r->rotSpeed));
    m->r->plane.y = oldPlaneX * sin((m->r->rotSpeed)) + m->r->plane.y * cos((m->r->rotSpeed));
}

void	move_right(t_mlx *m)
{
    //both camera direction and camera plane must be rotated
    double oldDirX = m->r->direction.x;
    m->r->direction.x = m->r->direction.x * cos(-(m->r->rotSpeed)) - m->r->direction.y * sin(-(m->r->rotSpeed));
    m->r->direction.y = oldDirX * sin(-(m->r->rotSpeed)) + m->r->direction.y * cos(-(m->r->rotSpeed));
    double oldPlaneX = m->r->plane.x;
    m->r->plane.x = m->r->plane.x * cos(-(m->r->rotSpeed)) - m->r->plane.y * sin(-(m->r->rotSpeed));
    m->r->plane.y = oldPlaneX * sin(-(m->r->rotSpeed)) + m->r->plane.y * cos(-(m->r->rotSpeed));
}
