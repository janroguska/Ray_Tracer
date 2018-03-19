/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:13:25 by jroguszk          #+#    #+#             */
/*   Updated: 2018/03/05 17:13:27 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RAY_TRACER_H
# define __RAY_TRACER_H
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "includes/libft/includes/libft.h"
# include "minilibx/mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# define WIDTH 800
# define HEIGHT 800
# define POS(i) (i < 0 ? -i : i)
# define ESC 53
# define MOTION_NOTIFY 6
# define MOTION_MASK (1L<<6)
# define RED 15
# define GREEN 5
# define BLUE 11
# define PURPLE 35
# define PLUS 24
# define MINUS 27
# define UP 126
# define DOWN 125
# define LEFT 124
# define RIGHT 123

typedef	struct	s_env
{
	int			bits;
	int			sizeline;
	int			endian;
	int			*addr;
	void		*mlx;
	void		*win;
	void		*img;
}				t_env;

typedef	struct	s_camera
{
	double	x;
	double	y;
	double	z;
}				t_camera;

typedef	struct	s_shape
{
	double	x;
	double	y;
	double	z;
	double	r;
	double	rx;
	double	ry;
	double	rz;
	double	s;
}				t_shape;

typedef	struct	s_direction
{
	double	x;
	double	y;
	double	z;
}				t_direction;

typedef	struct	s_read
{
	int		ret;
	int		fd;
	char	*line;
	char	*tmp;
}				t_read;

typedef	struct s_compute
{
	double	distx;
	double	disty;
	double	distz;
	double	discr;
	double	discrsq;
	double	t0;
	double	t1;
	double	a;
	double	b;
	double	c;
	double	y0;
	double	y1;
	double	th;
	double	v;
	double	vx;
	double	vy;
	double	vz;
	double	p;
	double	px;
	double	py;
	double	pz;
	double	vax;
	double	vay;
	double	vaz;
}				t_compute;

typedef	struct	s_master
{
	t_env		e;
	t_camera	c;
	t_direction	d;
	t_read		r;
	t_shape		s;
	t_list		*list;
	t_compute	t;
	int			i;
}				t_master;

int				main(int argc, char **argv);
int				draw(t_master *m);
int				key_hook(int keycode);
int				check_for_sphere(t_master *m, t_shape *s);
int				ft_round(double i);
int				read_file(t_master *m, char *argv);
int				check_input(t_master *m);
int				get_camera_coordinates(t_master *m);
int				get_object_coordinates(t_master *m);
void			allocate_coordinates(t_master *m, t_shape *s, int j, int i);
int				check_for_cylinder(t_master *m, t_shape *s);
int				cylinder_intersection(t_master *m);
void			initialize_coordinates(t_shape *s);
void			colour(t_master *m, t_shape *s, int i);
int				check_for_cone(t_master *m, t_shape *s);
void			rotate(t_master *m, t_shape *s);

#endif
