/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:07:33 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/26 10:52:55 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

/*
*Count the rows of a map 
*/
int	count_rows(char *map)
{
	char	*line;
	int		rows;
	int		fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		exit (error_exit(1));
	rows = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		rows++;
		line = get_next_line(fd);
	}
	close(fd);
	return (rows);
}

/*
*Function to get the coordinates of each line in the map
*/
t_vertex	*get_coords(char **line, int y, int rows, int max_len)
{
	t_vertex	*v;
	int			i;
	int			xlen;

	xlen = 0;
	while (line[xlen] && line[xlen][0] != '\n')
		xlen++;
	if (xlen < max_len)
		exit(error_exit(3));
	v = malloc(sizeof(t_vertex) * (max_len + 1));
	if (!v)
		exit(error_exit(1));
	i = 0;
	while (line[i] && i < max_len)
	{
		v[i].x = i;
		v[i].y = y;
		v[i].z = ft_atoi(line[i]);
		v[i].color = get_color(line[i]);
		v[i].size_x = max_len;
		v[i].size_y = rows;
		i++;
	}
	return (v);
}

/*
*Gets the length of the first line, and this is
*the one taken into account across the map.
*/
int	get_max_len(char *line)
{
	char	**linexyz;
	int		i;

	i = 0;
	linexyz = ft_split(line, ' ');
	while (linexyz[i] && (ft_isalnum(linexyz[i][0]) != 0
		|| linexyz[i][0] == '-'))
			i++;
	dblfree((void **)linexyz);
	return (i);
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
	int			max_len;

	i = 0;
	v = malloc(sizeof(t_vertex *) * (rows + 1));
	line = get_next_line(fd);
	max_len = get_max_len(line);
	while (line != NULL)
	{
		linexyz = ft_split(line, ' ');
		v[i] = get_coords(linexyz, i, rows, max_len);
		i++;
		free(line);
		dblfree((void **)linexyz);
		line = get_next_line(fd);
	}
	return (v);
}
