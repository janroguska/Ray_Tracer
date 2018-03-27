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
# define HEIGHT 600
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
# define To_Radians(Deg) ((Deg) * M_PI / 180.0)

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
	double	rx;
	double	ry;
	double	rz;
	double	dx;
	double	dy;
	double	dz;
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

typedef	struct	s_light
{
	double	x;
	double	y;
	double	z;
	double	px;
	double	py;
	double	pz;
	double	nx;
	double	ny;
	double	nz;
	double	angle;
}				t_light;

typedef	struct s_compute
{
	double	distx;
	double	disty;
	double	distz;
	double	discr;
	double	a;
	double	b;
	double	c;
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
	double	nx;
	double	ny;
	double	nz;
	double	len;
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
	t_light		l;
}				t_master;

int				main(int argc, char **argv);
int				draw(t_master *m);
int				key_hook(int keycode);
double			check_for_sphere(t_master *m, t_shape *s);
int				ft_round(double i);
int				read_file(t_master *m, char *argv);
int				check_input(t_master *m);
int				get_camera_coordinates(t_master *m);
int				get_object_coordinates(t_master *m);
void			allocate_coordinates(t_master *m, t_shape *s, int j, int i);
double			check_for_cylinder(t_master *m, t_shape *s);
void			initialize_coordinates(t_shape *s);
void			colour(t_master *m, t_shape *s);
double			check_for_cone(t_master *m, t_shape *s);
void			rotate(t_master *m, t_shape *s);
void			inner_product(t_master *m);
double			check_for_plane(t_master *m, t_shape *s);
void			check_shape(t_master *m, t_list *list);
void			normalize_vectors(t_master *m, t_shape *s);
double			get_t_value(t_master *m);
void			rotate_camera(t_master *m);
void			compute_ray_normal(t_master *m, t_shape *s);
void			get_angle(t_master *m, double len);
int				light_check(t_master *m, t_shape *s);

#endif
