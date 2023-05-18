/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:28:05 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/18 10:17:49 by msoria-j         ###   ########.fr       */
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

/*
*Free memory of a double pointer
*/
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

/*
*Simple function to get the absolute value of a number (int)
*/
int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

/*
*Simple function to get the absolute value of a number (float)
*/
float	ft_fabs(float nbr)
{
	if (nbr < 0)
		return (-nbr);
	else
		return (nbr);
}