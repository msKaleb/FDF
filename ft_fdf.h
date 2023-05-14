/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:19:59 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/14 12:44:38 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

# include "LibFT/libft.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>

/* Keys may vary depending on the OS */
# ifdef __linux__
#  define XK_ESCAPE 0xff1b
#  include "mlx_linux/mlx.h"	// MLX for Linux
# elif __APPLE__
#  define XK_ESCAPE 0x35
#  include "mlx/mlx.h"			// MLX for Mac
# endif /* OS Check */

# ifndef M_PI
#  define M_PI 3.14159265358979323846	// pi
# endif

/* Some needed values */
# define DEFAULT_COLOR 0xBADA55	// Badass color
# define TRUE_ISO 0.523599		// 30º angle
# define ISO 0.46373398			// 26.57º angle
# define DEFAULT_X 1024
# define DEFAULT_Y 768

/* Events and values for mlx_hook */
enum e_events{
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
	int	d;
	int	dx;
	int	dy;
	int	de;
	int	dne;
	int	scolor;
	int	fcolor;
}				t_trig;

typedef struct s_cam
{
	int	x;
	int	y;
	int	z;
	int	fov;
}				t_cam;

/* Functions prototipes */
t_vertex	*get_coords(char **line, int y, int rows);
t_vertex	**read_map(int fd, int rows);

t_trig		init_trig_var(t_vertex v1, t_vertex v2);

void		print_line(t_vertex v1, t_vertex v2, t_mlx m, t_trig t);
void		bresenham(t_vertex v1, t_vertex v2, t_mlx m);
void		print_vertex(t_mlx m, t_trig t, int color);
void		print_lines(t_vertex **v, t_mlx m);
void		xyztoperspective(t_vertex **v);
void		frame_map(t_vertex **v);
void		xyztoiso(t_vertex **v);
void		freemap(t_vertex **v);
void		dblfree(void **var);
void		init_mlx(t_mlx *m);

int			mouse_hook(int button, int x, int y, t_mlx *m);
int			gradient(t_trig t, float position);
int			key_hook(int key_code, t_mlx *m);
int			count_rows(char *map);
int			get_color(char *str);
int			close_mlx(t_mlx *m);
int			ft_abs(int n);

#endif /* FT_FDF_H */