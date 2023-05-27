/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:19:59 by msoria-j          #+#    #+#             */
/*   Updated: 2023/05/27 14:43:45 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_BONUS_H
# define FT_FDF_BONUS_H

# include "LibFT/libft.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>

/* Keys may vary depending on the OS */
# ifdef __linux__
#  include "mlx_linux/mlx.h"	// MLX for Linux
#  define XK_ESCAPE 	0xff1b
#  define XK_W 			0x77
#  define XK_A 			0x61
#  define XK_S 			0x73
#  define XK_D 			0x64
#  define XK_Q 			0x71
#  define XK_E 			0x65
#  define XK_P 			0x70
#  define XK_UP			0xff52
#  define XK_DOWN		0xff54
#  define XK_LEFT		0xff51
#  define XK_RIGHT		0xff53
# elif __APPLE__
#  include "mlx/mlx.h"			// MLX for Mac
#  define XK_ESCAPE 	0x35
#  define XK_W 			0x0d
#  define XK_A 			0x00
#  define XK_S 			0x01
#  define XK_D 			0x02
#  define XK_Q 			0x0c
#  define XK_E 			0x0e
#  define XK_P 			0x23
#  define XK_UP			0x7e
#  define XK_DOWN		0x7e
#  define XK_LEFT		0x7d
#  define XK_RIGHT		0x7b
# endif /* OS Check */

/* Not defined in my distro */
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

/* Some needed values */
# define DEFAULT_COLOR 	0xBADA55	// Badass color
# define TRUE_ISO 		0.523599	// 30º angle
# define ISO 			0.46373398	// 26.57º angle
# define DEFAULT_X 		1024.0		// float type for trig operations
# define DEFAULT_Y 		768.0		// float type for trig operations

/* Events and values for mlx_hook */
# define ON_KEYDOWN		2
# define ON_KEYUP		3
# define ON_MOUSEDOWN	4
# define ON_MOUSEUP		5
# define ON_MOUSEMOVE	6
# define ON_EXPOSE		12
# define ON_DESTROY		17
# define X_MASK			131072 // (1L << 17), for Linux
/* enum e_events{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
	X_MASK = (1L << 17)
}; */

typedef struct s_map_limits
{
	float	xmin;
	float	ymin;
	float	xmax;
	float	ymax;
	float	map_width;
	float	map_height;
}				t_map_limits;
typedef struct s_vertex
{
	float	x;
	float	y;
	float	z;
	float	scr_x;
	float	scr_y;
	int		color;
	int		size_x;
	int		size_y;
}				t_vertex;

typedef struct s_mlx
{
	t_vertex	**v;
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			bpp;
	int			sl;
	int			endian;
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
	float	x;
	float	y;
	float	z;
	float	pitch;
	float	yaw;
	int		fov;
}				t_cam;

/* Functions prototipes */
t_map_limits	get_limits(t_vertex **v);

t_vertex		**read_map(int fd, int rows);

t_trig			init_trig_var(t_vertex v1, t_vertex v2);

void			print_line(t_vertex v1, t_vertex v2, t_mlx m, t_trig t);
void			bresenham(t_vertex v1, t_vertex v2, t_mlx m);
void			print_vertex(t_mlx m, t_trig t, int color);
void			print_lines(t_vertex **v, t_mlx m);
void			xyztoperspective(t_mlx *m);
void			frame_map(t_vertex **v);
void			xyztoiso(t_vertex **v);
void			freemap(t_vertex **v);
void			center_map(t_mlx *m);
void			dblfree(void **var);
void			init_mlx(t_mlx *m);

float			ft_fabs(float nbr);

int				mouse_hook(int button, int x, int y, t_mlx *m);
int				key_hook(int key_code, t_mlx *m);
int				count_rows(char *map);
int				error_exit(int code);
int				get_color(char *str);
int				close_mlx(t_mlx *m);
int				ft_abs(int n);

/* Bonus part */
void			rotate_map(t_vertex **v, t_mlx *m, float angle);
void			zoom(t_mlx *m, int x, int y, int dir);
void			move_map(t_mlx *m, int x, int y);

#endif /* FT_FDF_BONUS_H */