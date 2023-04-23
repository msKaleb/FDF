/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:42:58 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/23 17:32:47 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"mlx_linux/mlx.h" // For Linux
// #include"mlx/mlx.h"
#include"fdf.h"
#include"libft/libft.h"
#include<fcntl.h>

// TODO:
// Gradient color from a to b function

void	get_coords(char **line)
{
	t_vertex	v;
	int	x;
	int	y;
	
	while (*line)
	{
		
		ft_fprintf(1, "%d ", ft_atoi(*line));
		line++;
	}
}

int	main(void)
{
	void	*mlx;
	void	*mlx_window;
	void	*mlx_image;
	char	*addr;
	char	*test_file = "maps/42.fdf";
	int		bpp;
	int		sl;
	int		endian;
	void	*ptr;
	int		color = 0x00FF0000;
	
	// char	c = 255;
	// ft_fprintf(1, "%d\n", 255 << 8);
	// exit(0);
	
	int	fd = open(test_file, O_RDONLY);
	char	*line;


	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, 640, 480, "Test");
	mlx_image = mlx_new_image(mlx, 640, 480);
	addr = mlx_get_data_addr(mlx_image, &bpp, &sl, &endian);
	// mlx_string_put(mlx, mlx_window, 100, 100, 0xeaf1f4, "Mikelo pargelo");

	ptr = addr;
	int x = -1;
	int y = 0;
	char **linexyz;
	
	while((line = get_next_line(fd)) != NULL)
	{
		linexyz = ft_split(line, ' ');
		get_coords(linexyz);
		ft_fprintf(1, "\n");
		while (line[++x])
		{
			if (line[x] != ' ')
				mlx_pixel_put(mlx, mlx_window, x, y, 255);
			else
				mlx_pixel_put(mlx, mlx_window, x, y, 255255);

		}
		y++;
		x = -1;
		// line = get_next_line(fd);
	}
	
	// mlx_put_image_to_window(mlx, mlx_window, mlx_image, 0, 0);
	// exit(0);
	
	
	ft_fprintf(1, "bpp: %d\n", bpp);
	ft_fprintf(1, "sl: %d\n", sl);
	close(fd);
	mlx_loop(mlx);

	for (int y = 0; y < 480; y++){
		for(int x = 0; x < sl; x++){
			ptr = addr + (y * sl + x * (bpp / 8));
			*(unsigned int*)ptr = color + y;
		}
	}
	mlx_destroy_image(mlx, mlx_image);
	mlx_destroy_window(mlx, mlx_window);
	
}
