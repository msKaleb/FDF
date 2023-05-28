/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:28:05 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/28 12:01:08 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

/*
*Iterate through the array freeing all the vertices
*/
void	freemap(t_vertex **v)
{
	int	i;
	int	rows;

	i = 0;
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
*Simple function to get the absolute value of a number
*/
float	ft_abs(float nbr)
{
	if (nbr < 0)
		return (-nbr);
	else
		return (nbr);
}

/*
*Error management. List of codes:
**	0 = Wrong number of arguments
**	1 = Error upon opening file
**	2 = Error on memory allocation
**	3 = Wrong fdf format
*/
int	error_exit(int code)
{
	if (code == 0)
		ft_fprintf(2, "\e[1;31mUsage: ./fdf map.fdf.\e[m\n");
	if (code == 1)
		ft_fprintf(2, "\e[1;31mCould not read the file. Exiting.\e[m\n");
	if (code == 2)
		ft_fprintf(2, "\e[1;31mError on malloc operation. Exiting.\e[m\n");
	if (code == 3)
		ft_fprintf(2, "\e[1;31mFound wrong line length. Exiting.\e[m\n");
	return (EXIT_FAILURE);
}
