/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:32:07 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/14 12:37:16 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	get_max_x(t_vertex **v)
{
	int	i;
	int	j;
	int	max;

	max = INT_MIN;
	i = -1;
	j = -1;
	while (++i < v[0]->size_y)
	{
		while (++j < v[i]->size_x)
			if (v[i][j].x < min)
				min = v[i][j].x;
		j = -1;
	}
	return (max);
}

void	frame_map(t_vertex **v)
{
	int	max;

	max = get_max_x(v);
}