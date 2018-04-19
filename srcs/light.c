/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 11:07:54 by jroguszk          #+#    #+#             */
/*   Updated: 2018/03/27 11:07:56 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer.h"

void	compute_ray_normal(t_master *m, t_shape *s)
{
	double	len;

	m->l.surface_x = m->c.camera_origin_x + m->t.normalized_direction_x * m->t.t_value;
	m->l.surface_y = m->c.camera_origin_y + m->t.normalized_direction_y * m->t.t_value;
	m->l.surface_z = m->c.camera_origin_z + m->t.normalized_direction_z * m->t.t_value;
	m->l.light_normal_x = m->l.surface_x - s->shape_origin_x;
	m->l.light_normal_y = m->l.surface_y - s->shape_origin_y;
	m->l.light_normal_z = m->l.surface_z - s->shape_origin_z;
	if (s->shape_id != 0.0)
		get_normal(m, s);
	len = sqrt((m->l.light_normal_x * m->l.light_normal_x)
	+ (m->l.light_normal_y * m->l.light_normal_y)
	+ (m->l.light_normal_z * m->l.light_normal_z));
	m->l.light_normal_x /= len;
	m->l.light_normal_y /= len;
	m->l.light_normal_z /= len;
}

void	get_normal(t_master *m, t_shape *s)
{
	double	dot_product;
	double	normal_origin_x;
	double	normal_origin_y;
	double	normal_origin_z;

	{
		dot_product = (m->l.light_normal_x * m->t.vax) + (m->l.light_normal_y * m->t.vay)
		+ (m->l.light_normal_z * m->t.vaz);
		normal_origin_x = s->shape_origin_x + dot_product * m->t.vax;
		normal_origin_y = s->shape_origin_y + dot_product * m->t.vay;
		normal_origin_z = s->shape_origin_z + dot_product * m->t.vaz;
		m->l.light_normal_x = m->l.surface_x - normal_origin_x;
		m->l.light_normal_y = m->l.surface_y - normal_origin_y;
		m->l.light_normal_z = m->l.surface_z - normal_origin_z;
	}
}

void	get_angle(t_master *m, t_light *l)
{
	double	len;

	len = sqrt((l->light_origin_x * l->light_origin_x)
	+ (l->light_origin_y * l->light_origin_y)
	+ (l->light_origin_z * l->light_origin_z));
	if (l->ambience > 1.0)
		l->ambience = 1.0;
	if (l->intensity > 1.0)
		l->intensity = 1.0;
	m->l.angle = ((l->light_origin_x / len) * m->l.light_normal_x)
	+ ((l->light_origin_y / len) * m->l.light_normal_y)
	+ ((l->light_origin_z / len) * m->l.light_normal_z);
	if (m->l.angle >= 0.0)
		m->l.angle = (m->l.angle * l->intensity) + l->ambience;
	else
		m->l.angle = l->ambience;
	if (l->intensity < 0.0)
		m->l.angle = 0.0;
	if (m->l.angle > 1.0)
		m->l.angle = 1.0;
	m->l.colour = l->ambience * 255;
	m->l.angle *= 255;
}

double	light_check(t_master *m, t_shape *s, t_list *list)
{
	double	i;
	t_list	*tmp;
	t_light	*l;

	tmp = m->light;
	l = (t_light*)tmp->content;
	compute_ray_normal(m, s);
	get_angle(m, l);
	m->c.direction_x = l->light_origin_x;
	m->c.direction_y = l->light_origin_y;
	m->c.direction_z = l->light_origin_z;
	m->c.camera_origin_x = m->l.surface_x + 0.000001;
	m->c.camera_origin_y = m->l.surface_y + 0.000001;
	m->c.camera_origin_z = m->l.surface_z + 0.000001;
	i = check_obstacle(m, list);
	if (i == 1.0)
		return (1.0);
	else
		return (0.0);
}

double	check_obstacle(t_master *m, t_list *list)
{
	double	i;
	int		a;
	t_shape *s;
	t_list	*tmp;

	tmp = list;
	while (tmp != NULL && tmp->content != NULL)
	{
		s = (t_shape*)tmp->content;
		i = shoot_ray(m, s);
		a = check_double_equality(i, m->t.ray_length);
		if (a == 1 && i >= 0.001)
			return (0.0);
		tmp = tmp->next;
	}
		return (1.0);
}

int		check_double_equality(double a, double b)
{
	double	diff;
	double	largest;

	diff = POS(a - b);
	a = POS(a);
	b = POS(b);
	largest = (b >= a) ? b : a;
	if (diff <= largest * 0.001)
		return (1);
	else
		return (0);
}