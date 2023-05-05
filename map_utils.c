/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:07:33 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/05 09:32:34 by msoria-j         ###   ########.fr       */
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
int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

/*Get rid of 'y' argument */
t_vertex	*get_coords(char **line, int y, int rows)
{
	t_vertex	*v;
	int			i;
	int			xlen;
	
	xlen = 0;
	while (line[xlen])
		xlen++;
	v = malloc(sizeof(t_vertex) * (xlen + 1));
	i = 0;
	if (!v)
		perror("");
	while (line[i])
	{
		// TODO: Find out a good offset for x and y
		// v[i].x = (DEFAULT_X / 3) + (i * ((DEFAULT_X / 3) / xlen));
		// v[i].y = y * ((DEFAULT_Y / 3) / rows);
		v[i].x = (DEFAULT_X / 2) + i * (DEFAULT_X / (xlen * 2));
		// ft_fprintf(1, "get_coords x: %d i: %d\n", v[i].x, i);
		v[i].y = y * ((DEFAULT_Y / 2) / rows);
		// v[i].x = (DEFAULT_X / 2) - (xlen * 2) + (i * 4);
		// v[i].y = (DEFAULT_Y / 2) - (rows * 2) + (y * 4);
		v[i].z = ft_atoi(line[i]) * 10;
		v[i].color = get_color(line[i]);
		v[i].size_x = xlen;
		v[i].size_y = rows;
		i++;
	}
	return (v);
}

/* get_z_limits calculates the boundaries of z value */
/* and apply an offset to it to have the map framed */
/* not used */
void	get_z_limits(t_vertex **v)
{
	int	i;
	int	j;
	int	nbr;

	nbr = INT_MIN;
	i = 0;
	j = -1;
	while (i < v[i]->size_y - 1)
	{
		while (++j < v[i]->size_x)
			if (ft_abs(v[i][j].z) > ft_abs(nbr))
				nbr = v[i][j].z;
		j = -1;
		i++;
	}
	i = 0;
	j = -1;
	while (i < v[i]->size_y - 1)
	{
		while (++j < v[i]->size_x)
			v[i][j].z = v[i][j].z * ((DEFAULT_Y / 3) / ft_abs(nbr));
		j = -1;
		i++;
	}
}

t_vertex	**read_map(int fd, int rows)
{
	t_vertex	**v;
	char		**linexyz;
	char		*line;
	int			i;
	
	i = 0;
	v = malloc(sizeof(t_vertex *) * (rows + 1));
	while((line = get_next_line(fd)) != NULL)
	{
		linexyz = ft_split(line, ' ');
		v[i] = get_coords(linexyz, i, rows);
		i++;
		free(line);
		dblfree((void **)linexyz);
	}
	// get_z_limits(v);
	return (v);
}
