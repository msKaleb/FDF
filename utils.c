/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:28:05 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/28 18:14:08 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	freemap(t_vertex **v)
{
	int i = 0;
	int	rows = v[0]->size_y;
	
	while (i < rows)
	{
		// ft_fprintf(1, "var[%d]: %s\n", i, v[i]->size_y);
		free(v[i]);
		i++;
	}
	free(v);
}

void	dblfree(void **var)
{
	int	i;

	i = 0;
	while (var[i]){
		free(var[i]);
		i++;
		}
	free(var);
}
