/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:19:59 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/25 10:51:49 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

# define DEFAULT_X 640
# define DEFAULT_Y 480

# include <stdio.h>

typedef struct s_vertex
{
	int	x;
	int	y;
	int	z;
	int	color;
}				t_vertex;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		bpp;
	int		sl;
	int		endian;
}				t_mlx;

#endif