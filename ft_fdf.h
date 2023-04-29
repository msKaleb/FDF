/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:19:59 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/29 19:27:27 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

/* MLX for Linux */
# include "mlx_linux/mlx.h"
/* MLX for Mac */
# include "mlx/mlx.h"
# include "LibFT/libft.h"
# include <stdio.h>
# include <math.h>

/* Keys may vary depending on the OS */
# ifdef __linux__
#  define XK_ESCAPE 0xff1b
# elif __APPLE__
#  define XK_ESCAPE 0x35
# endif

/* Some needed values */
# define DEFAULT_COLOR 0xBADA55	// Badass color
# define TRUE_ISO 0.523599		// 30º angle
# define ISO 0.46373398			// 26.57º angle
# define DEFAULT_X 640
# define DEFAULT_Y 480

/* Events and values for mlx_hook */
enum{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
	X_MASK = (1L << 17)
};

typedef struct s_vertex
{
	int	x;
	int	y;
	int	z;
	int	color;
	int	size_x;
	int	size_y;
}				t_vertex;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		bpp;
	int		sl;
	int		endian;
}				t_mlx;

typedef struct s_trig
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	z;
	int	m;
	int	d;
	int	dx;
	int	dy;
	int	de;
	int	dne;
}				t_trig;

/* Functions prototipes */
void	dda_line(t_vertex v1, t_vertex v2, t_mlx *m);
void	bresenham(t_vertex v1, t_vertex v2, t_mlx m);
void	put_vertex(t_vertex v, t_mlx m);
void	freemap(t_vertex **v);
void	dblfree(void **var);
int		get_color(char *str);

#endif