/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:19:59 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/26 10:26:11 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

/* XK_MISCELLANY for stander key events */
# define XK_MISCELLANY

/* Some needed values */
# define DEFAULT_X 640
# define DEFAULT_Y 480
# define TRUE_ISO 0.523599
# define ISO 0.46373398

/* Events for mlx_hook */
# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6
# define ON_EXPOSE 12
# define ON_DESTROY 17

# include <stdio.h>
# include <math.h>
# include "keysymdef.h"

typedef struct s_vertex
{
	int	x;
	int	y;
	int	z;
	int	color;
}				t_vertex;

/* Make a linked list to dinamically add rows */
typedef struct s_vlist
{
	t_vertex		*v;
	struct s_vlist	*next;
}				t_vlist;

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