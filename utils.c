/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:28:05 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/10 13:08:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	freemap(t_vertex **v)
{
	int i = 0;
	int	rows;
	
	rows = v[0]->size_y;
	while (i < rows)
	{
		free(v[i]);
		i++;
	}
	free(v);
}

void	dblfree(void **var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		free(var[i]);
		i++;
	}
	free(var);
}
