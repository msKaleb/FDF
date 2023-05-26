/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:11:37 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/26 12:18:26 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	map_ops(int key_code, t_mlx *m)
{
	if (key_code == XK_Q)
		rotate_map(m->v, m, 10);
	if (key_code == XK_E)
		rotate_map(m->v, m, -10);
	if (key_code == XK_A)
		move_map(m, -50, 0);
	if (key_code == XK_D)
		move_map(m, 50, 0);
	if (key_code == XK_W)
		move_map(m, 0, -50);
	if (key_code == XK_S)
		move_map(m, 0, 50);
	return (0);
}

// mlx_destroy_image(m->mlx, m->img);
int	close_mlx(t_mlx *m)
{
	freemap(m->v);
	mlx_destroy_window(m->mlx, m->win);
	free(m->mlx);
	system("leaks fdf"); // quitar
	exit(EXIT_SUCCESS);
}

// ft_fprintf(1, "%s\n", change_base((unsigned long long)key_code, 'x'));
int	key_hook(int key_code, t_mlx *m)
{
	if (key_code == XK_ESCAPE)
		close_mlx(m);
	if (key_code == XK_P)
		xyztoperspective(m);
	else
		map_ops(key_code, m);
	return (0);
}

// (void)m;
// ft_fprintf(1, "%d - %d - %d\n", button, x, y);
int	mouse_hook(int button, int x, int y, t_mlx *m)
{
	if (button == 4)
		zoom(m, x, y, 1);
	if (button == 5)
		zoom(m, x, y, -1);
	return (0);
}

void	init_mlx(t_mlx *m)
{
	m->mlx = mlx_init();
	if (m->mlx == NULL)
		exit (error_exit(2));
	m->win = mlx_new_window(m->mlx, DEFAULT_X, DEFAULT_Y, \
		"FDF Project - msoria-j");
	if (m->win == NULL)
		exit (error_exit(2));
	m->img = mlx_new_image(m->mlx, DEFAULT_X, DEFAULT_Y);
	if (m->img == NULL)
		exit (error_exit(2));
	m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->endian);
}
