/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:35:10 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/12 17:31:16 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_map			*init_map(void)
{
	t_map				*map;

	map = (t_map *)malloc(sizeof(*map));
	map->width = 0;
	map->height = 0;
	map->map = NULL;
	map->start.x = 0;
	map->start.y = 0;
	return (map);
}

int				read_validate_first_line(t_map **map, int fd)
{
	char				*line;
	char				*tmp;
	char				**args;

	line = NULL;
	get_next_line(fd, &line);
	tmp = replace_char(line, 'x', ' ');
	args = strsplit(tmp);
	ft_print_strings(args);
	if (ptr_count(args) != 2)
	{
		printf("ptr_count = %d\n", ptr_count(args));
		return (0);
	}
	(*map)->width = ft_atoi(args[0]);
	(*map)->height = ft_atoi(args[1]);
	return (1);
}

int				validate_line(char *line, t_map **map)
{
	int					p;
	static int 			line_num = 0;

	p = 0;
	while (line[p])
	{
		if (line[p] == 'S')
		{
			(*map)->start.x = p + .5;
			(*map)->start.y = line_num + .5;
			line[p] = '0';
		}
		else if (line[p] != '0' && line[p] != '1')
		{
			return (0);
		}
		p += 1;
	}
	line_num += 1;
	if (p != (*map)->width)
		return (0);
	return (1);
}

int				validate_map(t_map **map, int fd)
{
	char				*line;
	char				**map_;
	int					p;

	line = NULL;
	map_ = (char **)malloc(sizeof(char *) * ((*map)->height + 1));
	p = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (!validate_line(line, map))
			return (0);
		map_[p] = ft_strdup(line);
		p += 1;
		free(line);
		line = NULL;
	}
	map_[p] = NULL;
	printf("start at [%f][%f]\n", (*map)->start.y, (*map)->start.x);
	ft_print_strings(map_);
	(*map)->map = map_;
	return (1);
}

t_map			*read_validate_map(char *filename)
{
	t_map				*map;
	int					fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = init_map();

	if (!read_validate_first_line(&map, fd))
		return (NULL);
	printf("map->width = %d\nmap->height = %d\n", map->width, map->height);
	if (!validate_map(&map, fd))
		return (NULL);
	return (map);
}
