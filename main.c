/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:42:58 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/25 10:56:50 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"mlx_linux/mlx.h" // For Linux
// #include"mlx/mlx.h"
#include"ft_fdf.h"
#include"LibFT/libft.h"
#include<fcntl.h>

// TODO:
// Gradient color from a to b function

/* t_vertex	*get_coords(char **line)
{
	t_vertex	*v;
	int		i;
	int		n;
	
	i = 0;
	while (line[i])
		i++;
	v = malloc(sizeof(v) * i);
	n = i;
	i = -1;
	while(++i < n)
	{
		v[i].x = 20 + i * (640 / n);
		v[i].z = ft_atoi(line[i]);
		ft_fprintf(1, "%d-", v[i].z);
	}
	return (v);
} */

/* Change the value of x and y, maybe with macros */
/* Maybe change the arguments of the function */
t_vertex	*get_coords(char **line, int y)
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
		v[i].x = i * (DEFAULT_X / xlen);
		v[i].y = y;
		v[i].z = ft_atoi(line[i]);
		if (ft_strchr(line[i], ','))
			v[i].color = ft_atoi(ft_strchr(line[i], ',')); // change to decimal, then to int
		else
			v[i].color = 0xFFFFFF;
		i++;
	}
	return (v);
}

void	dblfree(void **var)
{
	int	i;

	i = -1;
	while (var[++i])
		free(var[i]);
	free(var);
}

int	keyhook(int key_code, t_mlx *m)
{
	// ft_fprintf(1, "%s\n", change_base(key_code, 'x'));
	if (key_code == 0xff1b)
	{
		mlx_destroy_image(m->mlx, m->img);
		mlx_destroy_window(m->mlx, m->win);		
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	main(void)
{
	t_vertex	*v;
	char	**linexyz;
	int x = -1;
	int y = 0;
	
	char	*line;
	int		fd;
	char	*test_file = "maps/42.fdf";
	
	ft_fprintf(1, "%d\n", ft_atoi("0xFFFFFF"));
	exit(0);
	fd = open(test_file, O_RDONLY);
	if (fd == -1)
		perror("Error"); // exit on error, make a function
	while((line = get_next_line(fd)) != NULL)
	{
		linexyz = ft_split(line, ' ');
		v = get_coords(linexyz, y);
		while (linexyz[++x])
			// ft_fprintf(1, "it: %d - x: %d - str: %s\n", x, v[x].x, linexyz[x]);
			ft_fprintf(1, "x: %d - y: %d - z: %d - color: \n", v[x].x, v[x].y, v[x].z, v[x].color);
		ft_fprintf(1, "\n");
		y++;
		x = -1;
		free(v);
		free(line);
		dblfree((void **)linexyz);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

/* int	main(void)
{
	t_mlx	m;
	
	char	*test_file = "maps/42.fdf";
	// int		bpp;
	// int		sl;
	// int		endian;
	void	*ptr;
	int		color = 0x00FF0000;
	t_vertex	*v;
	// char	c = 255;
	// ft_fprintf(1, "%d\n", 255 << 8);
	// exit(0);
	
	int		fd;
	char	*line;


	m.mlx = mlx_init();
	m.win = mlx_new_window(m.mlx, 640, 480, "Test");
	m.img = mlx_new_image(m.mlx, 640, 480);
	m.addr = mlx_get_data_addr(m.img, &m.bpp, &m.sl, &m.endian);

	ptr = m.addr;
	int x = -1;
	int y = 0;
	char **linexyz;
	ptr = &x;
	

	
	fd = open(test_file, O_RDONLY);
	if (fd == -1)
		perror("");
	while((line = get_next_line(fd)) != NULL)
	{
		linexyz = ft_split(line, ' ');
		v = get_coords(linexyz);
		
		while (linexyz[++x])
		{
			color = v[x].z + 0xffffff;
			mlx_pixel_put(m.mlx, m.win, v[x].x, y * (480 / 11), color);
			// ft_fprintf(1, "x: %d ", v[x].x);
			// if (line[x] != ' ')
			// 	mlx_pixel_put(m.mlx, m.win, x, y, 255);
			// else
			// 	mlx_pixel_put(m.mlx, m.win, x, y, 255255);

		}
		ft_fprintf(1, "\n");
		y++;
		x = -1;
		// free(v);
		// break;
		// line = get_next_line(fd);
	}
	
	mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
	// exit(0);
	

	
	ft_fprintf(1, "m.bpp: %d\n", m.bpp);
	ft_fprintf(1, "m.sl: %d\n", m.sl);
	close(fd);

	mlx_key_hook(m.win, &keyhook, &m);
	mlx_loop(m.mlx);
	
	for (int y = 0; y < 480; y++){
		for(int x = 0; x < m.sl; x++){
			ptr = m.addr + (y * m.sl + x * (m.bpp / 8));
			*(unsigned int*)ptr = color + y;
		}
	}

	
} */
