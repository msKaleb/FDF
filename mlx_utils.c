/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:11:37 by msoria-j          #+#    #+#             */
/*   Updated: 2023/06/02 10:05:39 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	close_mlx(t_mlx *m)
{
	freemap(m->v);
	mlx_destroy_window(m->mlx, m->win);
	free(m->mlx);
	exit(EXIT_SUCCESS);
}

int	key_hook(int key_code, t_mlx *m)
{
	if (key_code == XK_ESCAPE)
		close_mlx(m);
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
