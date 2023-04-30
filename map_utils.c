/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:07:33 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/30 18:42:01 by msoria-j         ###   ########.fr       */
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
		v[i].y = y * ((DEFAULT_Y / 2) / rows);
		// v[i].x = i * (DEFAULT_X / (xlen));
		// v[i].y = y * ((DEFAULT_Y) / rows);
		v[i].z = ft_atoi(line[i]); // TODO: Find a valid multiplier (depending on the max z value)
		v[i].color = get_color(line[i]);
		v[i].size_x = xlen;
		v[i].size_y = rows;
		i++;
	}
	return (v);
}

void	fill_max_z(t_vertex **v, int max_z)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	// ft_fprintf(1, "z: %d - mz: %d\n", v[0][0].z, max_z);
	// return ;
	while (i < v[i]->size_y - 1)
	{
		while (++j < v[i]->size_x)
		{
			v[i][j].z = v[i][j].z * ((DEFAULT_Y / 3) / max_z);
			ft_fprintf(1, "z: %d - mz: %d\n", v[i][j].z, max_z);
			ft_fprintf(1, "x: %d\n", v[0][0].x);
		}
		j = -1;
		i++;
	}
}

void	get_max_z(t_vertex **v)
{
	int	i;
	int	j;
	int	nbr;

	nbr = INT_MIN;
	i = 0;
	j = -1;
	// ft_fprintf(1, "nbr: %d\n", nbr);
	while (i < v[i]->size_y - 1)
	{
		while (++j < v[i]->size_x)
		{
			if (v[i][j].z > nbr)
			{
				nbr = v[i][j].z;
				// ft_fprintf(1, "v_mz: %d\n", v[i][j].z);
			}
		}
		j = -1;
		i++;
	}
	ft_fprintf(1, "mz: %d\n", nbr);
	fill_max_z(v, nbr);
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
	get_max_z(v);
	return (v);
}
