/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:42:58 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/22 19:08:39 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"mlx_linux/mlx.h"
#include"libft/libft.h"
// TODO:
// Gradient color from a to b function

int	main(void)
{
	void	*mlx;
	void	*mlx_window;
	void	*mlx_image;
	char	*addr;
	// char	*test_file = "maps/test_maps/42.fdf";
	int		bpp;
	int		sl;
	int		endian;
	void	*ptr;
	int		color = 0x00FF0000;
	
	char	c = 255;
	ft_fprintf(1, "%d\n", c << 8);
	exit(0);
	
	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, 640, 480, "Test");
	mlx_image = mlx_new_image(mlx, 640, 480);
	
	addr = mlx_get_data_addr(mlx_image, &bpp, &sl, &endian);
	// mlx_string_put(mlx, mlx_window, 100, 100, 0xeaf1f4, "Mikelo pargelo");

	ptr = addr;
	for (int y = 0; y < 480; y++){
		for(int x = 0; x < sl; x++){
			ptr = addr + (y * sl + x * (bpp / 8));
			*(unsigned int*)ptr = color + y;
		}
	}
	mlx_put_image_to_window(mlx, mlx_window, mlx_image, 0, 0);
	
	ft_fprintf(1, "bpp: %d\n", bpp);
	ft_fprintf(1, "sl: %d\n", sl);
	
	mlx_loop(mlx);

	mlx_destroy_image(mlx, mlx_image);
	mlx_destroy_window(mlx, mlx_window);
	
}
