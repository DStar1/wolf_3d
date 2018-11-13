/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:18:47 by hasmith           #+#    #+#             */
/*   Updated: 2018/11/12 17:33:55 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "wolf3d.h"

// /*
// ** Key hooks
// */

int		key_press_hook(int keycode, t_wolf *mast)
{
	printf("KEYCODE:  %d\n", keycode);
	if (keycode == 53)//exit
		exit(1);
	else if (keycode == 126)//up
		move_forward(mast);
	else if (keycode == 125)//down
		move_back(mast);
	else if (keycode == 124)//right
		move_right(mast);
	else if (keycode == 123)//left
		move_left(mast);
	// // else if (keycode == 49)//space
	// 	//jump?
	// // re_draw()
	start(mast, mast->map);
	
	return (0);
}

// /*
// ** Mouse hooks
// */

// // int		mouse_press_hook(int code, int x, int y, t_wolf *m){
// // 	/* MOUSE PRESS */
// // 	if (code == 1)
// // 	{

// // 	}
// // 	/* ZOOM OUT */
// // 	if (code == 4)
// // 	{

// // 	}
// // 	/* ZOOM IN */
// // 	if (code == 5)
// // 	{

// // 	}
// // 	return (0);
// // }

// // int			mouse_release_hook(int x, int y, t_wolf *m){
	
// // }

// int			mouse_motion_hook(int x, int y, tmaster *m)
// {
// 	m->mlx->mouse_x = x/10-(m->mlx->width/10);
// 	m->mlx->mouse_y = y/10-(m->mlx->height/10);
// 	//re_draw
// 	return (1);
// }

void		set_hooks(t_wolf *m)
{
	// mlx_hook(m->mlx->win, 12, 0, expose_hook, m);
	mlx_hook(m->mlx->win, 2, 0, key_press_hook, m);
	// mlx_hook(m->mlx->win, 3, 0, key_release_hook, m);
	
	// mlx_hook(m->mlx->win, 4, 0, mouse_press_hook, m);//uncomment

	// mlx_hook(m->mlx->win, 5, 0, mouse_release_hook, m);

	// mlx_hook(m->mlx->win, 6, 0, mouse_motion_hook, m);
	
	// mlx_hook(m->mlx->win, 17, 0, exit_hook, m);
}