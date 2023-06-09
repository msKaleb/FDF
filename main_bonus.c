/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:42:58 by msoria-j          #+#    #+#             */
/*   Updated: 2023/06/02 08:22:00 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_fdf.h"

int	main(int argc, char **argv)
{
	t_mlx		m;
	int			fd;

	if (argc != 2)
		return (error_exit(0));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (error_exit(1));
	init_mlx(&m);
	m.v = read_map(fd, count_rows(argv[1]));
	xyztoiso(m.v);
	frame_map(m.v);
	print_lines(m.v, m);
	mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
	mlx_key_hook(m.win, &key_hook, &m);
	mlx_mouse_hook(m.win, &mouse_hook, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx, &m);
	mlx_loop(m.mlx);
	close(fd);
	freemap(m.v);
	return (EXIT_SUCCESS);
}
