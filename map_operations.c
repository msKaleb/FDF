/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:27:31 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/19 11:54:27 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	rotate_map(t_vertex **v, t_mlx *m, float angle)
{
	float	angle_rad;
	float	tmpx;
	float	tmpy;
	int		i;
	int		j;

	i = -1;
	j = -1;
	angle_rad = angle * (M_PI / 180);
	while (++i < v[0]->size_y)
	{
		while (++j < v[i]->size_x)
		{
			tmpx = v[i][j].x;
			tmpy = v[i][j].y;
			v[i][j].x = tmpx * cos(angle_rad) - tmpy * sin(angle_rad);
			v[i][j].y = tmpy * sin(angle_rad) + tmpy * cos(angle_rad);
		}
		j = -1;
	}
	mlx_clear_window(m->mlx, m->win);
	print_lines(v, *m);
	// mlx_put_image_to_window(m.mlx, m.win, m.img, 0, 0);
}
