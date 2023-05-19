/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:11:37 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/19 12:04:02 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

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
