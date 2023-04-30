/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:07:33 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/30 13:11:56 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	count_rows(char *map)
{
	char	*line;
	int		rows;
	int		fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		perror("Error"); // exit on error, make a function	
	rows = 0;
	while((line = get_next_line(fd)) != NULL)
		rows++;
	close(fd);
	return (rows);
}

/*Get rid of 'y' argument */
t_vertex	*get_coords(char **line, int y, int rows)
{
	t_vertex	*v;
	int			i;
	int			xlen;
	
	i = 0;
	while (line[i])
		i++;
	xlen = i;
	v = malloc(sizeof(t_vertex) * (xlen + 1));
	i = 0;
	if (!v)
		perror("");
	while (line[i])
	{
		// TODO: Find out a nice offset for x and y
		// v[i].x = (DEFAULT_X / 3) + (i * ((DEFAULT_X / 3) / xlen));
		// v[i].y = y * ((DEFAULT_Y / 3) / rows);
		v[i].x = (DEFAULT_X / 2) + i * (DEFAULT_X / (xlen * 2));
		v[i].y = y * ((DEFAULT_Y / 2) / rows);
		// v[i].x = i * (DEFAULT_X / (xlen));
		// v[i].y = y * ((DEFAULT_Y) / rows);
		v[i].z = ft_atoi(line[i]) * 5; // TODO: Find a valid multiplier (depending on the max z value)
		if (ft_strchr(line[i], ',')) // TODO: implement this if-else inside get_color()
			v[i].color = get_color(ft_strchr(line[i], ',') + 1); // TODO: get lower case and incomplete numbers (0xff), to work
		else
			v[i].color = DEFAULT_COLOR;
		v[i].size_x = xlen;
		v[i].size_y = rows;
		i++;
	}
	return (v);
}

t_vertex	**read_map(int fd, int rows)
{
	t_vertex	**v;
	char		**linexyz;
	char		*line;
	int			i;
	
	i = 0;
	v = malloc(sizeof(t_vertex *) * (rows + 1));
	while((line = get_next_line(fd)) != NULL) // TODO: make a function to read the map
	{
		linexyz = ft_split(line, ' ');
		v[i] = get_coords(linexyz, i, rows);
		i++;
		free(line);
		dblfree((void **)linexyz);
	}
	return (v);
}
