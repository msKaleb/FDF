/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:11:37 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/22 12:20:32 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	map_ops(int key_code, t_mlx *m)
{
	if (key_code == XK_A)
		rotate_map(m->v, m, 45);
	if (key_code == XK_LEFT)
		move_map(m, -10, 0);
	if (key_code == XK_RIGHT)
		move_map(m, 10, 0);
	if (key_code == XK_UP)
		move_map(m, 0, -10);
	if (key_code == XK_DOWN)
		move_map(m, 0, 10);
	return (0);
}

// mlx_destroy_display(m->mlx);
int	close_mlx(t_mlx *m)
{
	mlx_destroy_image(m->mlx, m->img);
	mlx_destroy_window(m->mlx, m->win);
	free(m->mlx);
	exit(EXIT_SUCCESS);
}

// ft_fprintf(1, "%s\n", change_base((unsigned long long)key_code, 'x'));
int	key_hook(int key_code, t_mlx *m)
{
	if (key_code == XK_ESCAPE)
		close_mlx(m);
	else
		map_ops(key_code, m);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_mlx *m)
{
	(void)m;
	ft_fprintf(1, "%d - %d - %d\n", button, x, y);
	return (0);
}

void	init_mlx(t_mlx *m)
{
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, DEFAULT_X, DEFAULT_Y, \
		"FDF Project - msoria-j");
	m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->endian);
}
