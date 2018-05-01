/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:32:52 by jroguszk          #+#    #+#             */
/*   Updated: 2018/05/01 17:32:54 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer.h"

double	plane_shadow(t_master *m, t_shape *s, t_light *l)
{
	double	i;

	i = 0.0;
	if (s->shape_id != 3)
		return (1.0);
	m->c.direction_x = l->light_origin_x;
	m->c.direction_y = l->light_origin_y;
	m->c.direction_z = l->light_origin_z;
	normalize_vectors(m);
	i = shoot_ray(m, s);
	if (m->t.ray_length - i >= 0.00001 && i >= 0.0)
		return (0.0);
	else
		return (1.0);
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
		m->t.distx = m->c.camera_origin_x - s->shape_origin_x;
		m->t.disty = m->c.camera_origin_y - s->shape_origin_y;
		m->t.distz = m->c.camera_origin_z - s->shape_origin_z;
		m->t.vax = 0.0;
		m->t.vay = 1.0;
		m->t.vaz = 0.0;
		i = shoot_ray(m, s);
		if (m->t.ray_length - i >= 0.00001 && i >= 0.0)
			return (0.0);
		tmp = tmp->next;
	}
	return (1.0);
}
