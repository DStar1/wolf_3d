/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 00:26:23 by hasmith           #+#    #+#             */
/*   Updated: 2018/11/09 18:52:07 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


//mlx
/*
** creates a string with alocated space for all pixels on screen
*/

void	pixel_str(t_mlx *m)
{
	m->img_ptr = mlx_new_image(m->mlx, m->width, m->height);
	m->img_int = (int*)mlx_get_data_addr(
		m->img_ptr, &m->bpp, &m->size_line, &m->endian);
}

/*
** puts all pixles to screen, and then destroys the image
*/

void	create_image(t_mlx *m)
{
	mlx_put_image_to_window(m->mlx, m->win, m->img_ptr, 0, 0);
	// mlx_destroy_image(m->mlx, m->img_ptr);///maybe
	// mlx_clear_window(m->mlx, m->win);//////better?
}





void init(t_mlx *mast){
	mast->height = 1000;
	mast->width = 1000;
	mast->space = 0;
	mast->im_buff_size = mast->height * mast->width;
	mast->mouse_x = mast->width/2;
	mast->mouse_y = mast->height/2;
	mast->theme = 0;
}

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

int verLine(int x, int y1, int y2, int color, t_mlx *m){
	// m->img_int;//pixels

	// if(y2 < y1) {y1 += y2; y2 = y1 - y2; y1 -= y2;} //swap y1 and y2
	// if(y2 < 0 || y1 >= m->height  || x < 0 || x >= m->width) return 0; //no single point of the line is on screen
	// if(y1 < 0) y1 = 0; //clip
	// if(y2 >= m->width) y2 = m->height - 1; //clip

	// Uint32 colorSDL = SDL_MapRGB(scr->format, color.r, color.g, color.b);
	// Uint32* bufp;

	// m->img_int = scr->pixels + y1 * scr->pitch / 4 + x;
	for(int y = y1; y <= y2; y++)
	{
		pixel_put(m, x, y, color);
		// bufp += scr->pitch / 4;
	}
	return 1;
}

void			load_engine(t_map *map, t_mlx *m)
{
	ft_bzero(m, sizeof(*m));
	m->wsize = 1000;
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, m->wsize, m->wsize, "wolf3d");
	init(m);
	pixel_str(m);
	start(m, map);
	create_image(m);
}

void			wolf3d(char *mapname)
{
	t_map				*map;
	t_mlx				mast;
//	t_player			*player;


	map = read_validate_map(mapname);
	if (!map)
	{
		write(2, MAP_ERROR, sizeof(MAP_ERROR));
		return ;
	}
	load_engine(map, &mast);
	set_hooks(&mast);
	mlx_loop(mast.mlx);
//	player = init_player(map);
}

int		main(int argc, char *argv[])
{
	if (argc == 2)
	{
		wolf3d(argv[1]);
	}
	else
	{
		write(2, USAGE, sizeof(USAGE));
	}
	return (0);
}
