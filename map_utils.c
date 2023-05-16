/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:07:33 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/16 13:15:37 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

/*
*TODO:
**		check every line has the same length 
*Count the rows of a map 
*/
int	count_rows(char *map)
{
	int		rows;
	int		fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		perror("Error");
	rows = 0;
	while (get_next_line(fd) != NULL)
		rows++;
	close(fd);
	return (rows);
}

/* Simple function to get the absolute value of a number */
int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

/*
* TODO: 
**		Get a good z value
**		Adapt to Norm
*Calculates the boundaries of z value and
*apply an offset to it to have the map framed
*/
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
	if (ft_abs(nbr) < 5)
		return ;
	while (i < v[i]->size_y - 1)
	{
		while (++j < v[i]->size_x)
			v[i][j].z = v[i][j].z * ((DEFAULT_Y / 3) / nbr);
		j = -1;
		i++;
	}
}

/*
* TODO:	
**		Find out a good offset for x and y
** 		Get rid of 'y' argument
**		Check xlen is the same in every line (in count_rows())
*Function to get the coordinates of each line in the map
*/
t_vertex	*get_coords(char **line, int y, int rows)
{
	t_vertex	*v;
	int			i;
	int			xlen;

	xlen = 0;
	while (line[xlen] && line[xlen][0] != '\n')
		xlen++;
	v = malloc(sizeof(t_vertex) * (xlen + 1));
	i = 0;
	if (!v)
		perror("");
	while (line[i])
	{
		// v[i].x = i;
		// v[i].y = y;
		v[i].x = (DEFAULT_X / 2) + i * (DEFAULT_X / (xlen * 2));
		v[i].y = y * ((DEFAULT_Y / 2) / rows);
		v[i].z = ft_atoi(line[i]);
		v[i].color = get_color(line[i]);
		v[i].size_x = xlen;
		v[i].size_y = rows;
		i++;
	}
	return (v);
}

/*
Creates a double pointer that stores the map
*/
t_vertex	**read_map(int fd, int rows)
{
	t_vertex	**v;
	char		**linexyz;
	char		*line;
	int			i;

	i = 0;
	v = malloc(sizeof(t_vertex *) * (rows + 1));
	line = get_next_line(fd);
	while (line != NULL)
	{
		linexyz = ft_split(line, ' ');
		v[i] = get_coords(linexyz, i, rows);
		i++;
		free(line);
		dblfree((void **)linexyz);
		line = get_next_line(fd);
	}
	// get_z_limits(v);
	return (v);
}
