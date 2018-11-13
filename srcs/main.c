/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 18:53:49 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/12 19:07:35 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


//mlx
/*
** creates a string with alocated space for all pixels on screen
*/

void	pixel_str(t_wolf *m)
{
	m->mlx->img_ptr = mlx_new_image(m->mlx->mlx, m->mlx->width, m->mlx->height);
	m->mlx->img_int = mlx_get_data_addr(
		m->mlx->img_ptr, &(m->mlx->bpp), &(m->mlx->size_line), &(m->mlx->endian));
	m->mlx->bpp /= 8;
}

/*
** puts all pixles to screen, and then destroys the image
*/

void	create_image(t_wolf *m)
{
	mlx_put_image_to_window(m->mlx->mlx, m->mlx->win, m->mlx->img_ptr, 0, 0);
	// mlx_destroy_image(m->mlx->mlx, m->mlx->img_ptr);///maybe
	// mlx_clear_window(m->mlx->mlx, m->mlx->win);//////better?
}




void init(t_wolf *m){
	m->mlx->height = 1000;
	m->mlx->width = 1000;
	m->mlx->space = 0;
	m->mlx->im_buff_size = m->mlx->height * m->mlx->width;
	m->mlx->mouse_x = m->mlx->width/2;
	m->mlx->mouse_y = m->mlx->height/2;
	m->mlx->theme = 0;
}

void pixel_put(t_wolf *m, int x, int y, int color){
	if (x < m->mlx->wsize && y < m->mlx->wsize)
		// if (y >= 0 && x >= 0) /////Maybe add back
		{
		//	printf("bpp = %d\n", m->mlx->bpp);
//			m->mlx->bpp = 4;
			m->mlx->img_int[y * m->mlx->size_line + x * m->mlx->bpp] = color;
	m->mlx->img_int[y * m->mlx->size_line + x * m->mlx->bpp + 1] = color >> 8;
	m->mlx->img_int[y * m->mlx->size_line + x * m->mlx->bpp + 2] = color >> 16;
		//	int i = (x) + (y * m->mlx->size_line / 4);
			// m->mlx->img_int[((y * m->mlx->size_line/4) + x)] = color;
//			m->mlx->img_int[i] = color;
//			m->mlx->img_int[++i] = color >> 8;
//			m->mlx->img_int[++i] = color >> 16;
		}
}

int verLine(int x, int y1, int y2, int color, t_wolf *m){
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

void			load_engine(t_wolf *m)
{
	m->mlx->wsize = 1000;
	m->mlx->mlx = mlx_init();
	m->mlx->win = mlx_new_window(m->mlx->mlx, m->mlx->wsize, m->mlx->wsize, "wolf3d");
	init(m);
	pixel_str(m);
	start(m);

}

void			wolf3d(char *mapname)//, t_mlx *mast)
{
	// t_map				*map;
	t_wolf				*mast;
	t_raycast			*r;

	mast = malloc(sizeof(t_wolf));
	ft_bzero(mast, sizeof(*mast));
	r = malloc(sizeof(*r));
	mast->mlx = malloc(sizeof(t_mlx));
	mast->r  = r;
	// mast->mlx->wsize = 100;
	printf("Wsize: %d", mast->mlx->wsize);
	mast->map = read_validate_map(mapname);
	if (!mast->map)
	{
		write(2, MAP_ERROR, sizeof(MAP_ERROR));
		return ;
	}
	init_raycast_vars(mast);
	// mast->r = r;
	// ft_memcpy(r,mast->r,sizeof(*mast->r));
	// mast->map = map;
	// printf("you did it %f\n", mast->r->plane.y);
	// printf("address of r = %p\n", mast->r);
	// ft_memcpy(map,mast->map,sizeof(*mast->map));

	load_engine(mast);
	
	set_hooks(mast);
	mlx_loop(mast->mlx->mlx);
}

int		main(int argc, char *argv[])
{
	if (argc == 2)
	{
		wolf3d(argv[1]);//, &mast);
	}
	else
	{
		write(2, USAGE, sizeof(USAGE));
	}
	return (0);
}
