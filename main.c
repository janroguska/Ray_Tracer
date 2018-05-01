/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:06:10 by jroguszk          #+#    #+#             */
/*   Updated: 2018/03/05 17:06:35 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer.h"

int		main(int argc, char **argv)
{
	t_master	m;

	m.list = ft_lstnew(NULL, 0);
	m.e.resolution = 1.0;
	if (argc != 2)
		return (0);
	m.e.mlx = mlx_init();
	m.e.win = mlx_new_window(m.e.mlx, WIDTH, HEIGHT, "RAYYYYY!!!");
	m.e.img = mlx_new_image(m.e.mlx, WIDTH, HEIGHT);
	m.e.addr = (int*)mlx_get_data_addr(m.e.img, &m.e.bits,
	&m.e.sizeline, &m.e.endian);
	read_file(&m, argv[1]);
	draw(&m);
	mlx_key_hook(m.e.win, key_hook, &m);
	mlx_put_image_to_window(m.e.mlx, m.e.win, m.e.img, 0, 0);
	mlx_loop(m.e.mlx);
	return (0);
}

int		ft_round(double i)
{
	return (i < 0 ? i - 0.5 : i + 0.5);
}

int		draw(t_master *m)
{
	t_list	*tmp;

	m->d.z = -WIDTH / 2;
	m->d.y = 0.0;
	tmp = m->list;
	while (m->d.y < HEIGHT)
	{
		m->d.x = 0.0;
		while (m->d.x < WIDTH)
		{
			check_shape(m, tmp);
			m->d.x += m->e.resolution;
		}
		m->d.y += m->e.resolution;
	}
	mlx_put_image_to_window(m->e.mlx, m->e.win, m->e.img, 0, 0);
	return (0);
}

void	check_shape(t_master *m, t_list *list)
{
	double		i;
	double		j;
	int			k;
	t_shape		*s;
	t_list		*tmp;

	j = 0.0;
	k = 0;
	tmp = list;
	m->c.direction_x = m->d.x;
	m->c.direction_y = m->d.y;
	m->c.direction_z = m->d.z;
	normalize_vectors(m);
	rotate_camera(m);
	while (tmp != NULL && tmp->content != NULL)
	{
		s = (t_shape*)tmp->content;
		m->t.distx = m->c.camera_origin_x - s->shape_origin_x;
		m->t.disty = m->c.camera_origin_y - s->shape_origin_y;
		m->t.distz = m->c.camera_origin_z - s->shape_origin_z;
		m->t.vax = 0.0;
		m->t.vay = 1.0;
		m->t.vaz = 0.0;
		i = shoot_ray(m, s);
		if (k == 0)
			j = i;
		if (i >= 0 && (i <= j || j < 0))
		{
			j = i;
			colour(m, s, list);
		}
		tmp = tmp->next;
		k++;
	}
}

double	shoot_ray(t_master *m, t_shape *s)
{
	double	i;

	i = -0.000001;
	if (s->shape_id == 0)
		i = check_for_sphere(m, s);
	else if (s->shape_id == 1)
		i = check_for_cylinder(m, s);
	else if (s->shape_id == 2)
		i = check_for_cone(m, s);
	else if (s->shape_id == 3)
		i = check_for_plane(m, s);
	return (i);
}

int		key_hook(int keycode)
{
	if (keycode == ESC)
		exit(0);
	return (0);
}

void	colour(t_master *m, t_shape *s, t_list *list)
{
	double		i;
	t_master	a;

	ft_memcpy(&a, m, sizeof(t_master));
	if ((i = light_check(&a, s, list)) == 0.0)
		a.l.angle = a.l.colour;
	if (s->shape_id == 0.0)
		m->e.addr[ft_round(m->d.x + (m->d.y * WIDTH))] = ft_round(a.l.angle) * 256 * 256;
	else if (s->shape_id == 1.0)
		m->e.addr[ft_round(m->d.x + (m->d.y * WIDTH))] = ft_round(a.l.angle) * 256;
	else if (s->shape_id == 2.0)
		m->e.addr[ft_round(m->d.x + (m->d.y * WIDTH))] = ft_round(a.l.angle);
	else if (s->shape_id == 3.0)
		m->e.addr[ft_round(m->d.x + (m->d.y * WIDTH))] = ft_round(a.l.angle) * 256 * 256;
}

void	ft_clear(t_master *m)
{
	int		i;
	int		j;

	i = 0;
	j = HEIGHT * WIDTH;
	while (i < j)
	{
		m->e.addr[i] = 0x000000;
		i++;
	}
}
