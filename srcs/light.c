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
	len = sqrt((m->l.light_normal_x * m->l.light_normal_x)
	+ (m->l.light_normal_y * m->l.light_normal_y)
	+ (m->l.light_normal_z * m->l.light_normal_z));
	m->l.light_normal_x /= len;
	m->l.light_normal_y /= len;
	m->l.light_normal_z /= len;
	get_angle(m, len);
}

void	get_angle(t_master *m, double len)
{
	double	dot;

	dot = (m->t.normalized_direction_x * m->l.light_normal_x)
	+ (m->t.normalized_direction_y * m->l.light_normal_y)
	+ (m->t.normalized_direction_z * m->l.light_normal_z);
	m->l.angle = cos(dot / (m->t.t_value * len));
}

double	light_check(t_master *m, t_shape *s, t_list *list)
{
	double	i;
	t_list	*tmp;
	t_light	*l;

	tmp = m->light;
	l = (t_light*)tmp->content;
	compute_ray_normal(m, s);
	m->c.camera_origin_x = l->light_origin_x;
	m->c.camera_origin_y = l->light_origin_y;
	m->c.camera_origin_z = l->light_origin_z;
	m->c.direction_x = m->l.surface_x;
	m->c.direction_y = m->l.surface_y;
	m->c.direction_z = m->l.surface_z;
	i = check_obstacle(m, list);
	if (i == 1.0)
		return (1.0);
	else
		return (0.0);
}

double	check_obstacle(t_master *m, t_list *list)
{
	double	i;
	t_shape *s;
	t_list	*tmp;

	tmp = list;
	while (tmp != NULL && tmp->content != NULL)
	{
		s = (t_shape*)tmp->content;
		i = shoot_ray(m, s);
		if (POS(m->t.ray_length - i) >= 0.01 && i >= 0)
			return (0.0);
		tmp = tmp->next;
	}
		return (1.0);
}