/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:42:58 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/19 11:21:15 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_fdf.h"

/*
* TODO:
**		Input error management
**  	Implement perspective projection
*/
int	main(int argc, char **argv)
{
	t_vertex	**v;
	t_mlx		m;
	int			fd;
	
	if (argc != 2)
		return (EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	v = read_map(fd, count_rows(argv[1]));
	init_mlx(&m);
	print_lines(v, m);
	freemap(v);
	mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
	mlx_key_hook(m.win, &key_hook, &m);
	mlx_mouse_hook(m.win, &mouse_hook, &m);
	mlx_hook(m.win, ON_DESTROY, X_MASK, &close_mlx, &m);
	mlx_loop(m.mlx);
	close(fd);
	return (EXIT_SUCCESS);
}
