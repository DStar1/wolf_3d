/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 00:26:23 by hasmith           #+#    #+#             */
/*   Updated: 2018/11/07 00:35:09 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void pixel_put(t_mlx *mlx, int x, int y, int color){
	if (x < mlx->wsize && y < mlx->wsize)
		// if (y >= 0 && x >= 0) /////Maybe add back
		{
			int i = (x) + (y * mlx->size_line / 4);
			// mlx->img_int[((y * mlx->size_line/4) + x)] = color;
			mlx->img_int[i] = color;
			mlx->img_int[++i] = color >> 8;
			mlx->img_int[++i] = color >> 16;
		}
}

/*
** Muti-threading
*/

static void *draw_in_thread(void *arg){
	t_thread	*thread;
	t_mlx *mast;
	int height;
	int y;

	thread = (t_thread*)arg;
	mast = thread->m;
	height = (thread->count * (mast->height/4)) + (mast->height/4);
	y = (mast->height/4) * thread->count;
	for(; y<height; ++y)
	{
		if (mast->theme == 1){
			//themes to draw
		}
		else if (mast->theme == 2){
			//themes to draw
		}
	}
	return (mast);
}

void draw_frac(t_mlx *mast){
	// mlx_destroy_image(mast->mlx, mast->img_ptr);
	// mlx_clear_window(mast->mlx, mast->win);

	int			i;
	t_thread	*thread;
	pthread_t	tid[4];

	i = -1;
	pixel_str(mast);
	thread = ft_memalloc(sizeof(t_thread) * 4);
	while (++i < 4)
	{
		thread[i].m = mast;
		thread[i].count = i;
		pthread_create(&tid[i], NULL, draw_in_thread, &thread[i]);
	}
	i = -1;
	while (++i < 4)
	{
		pthread_join(tid[i], NULL);
	}
	// mlx_clear_window(mast->mlx, mast->win);
	create_image(mast);//new
	free(thread);
}