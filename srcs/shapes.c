/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:43:28 by jroguszk          #+#    #+#             */
/*   Updated: 2018/03/12 14:43:30 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer.h"

double	check_for_sphere(t_master *m, t_shape *s)
{
	normalize_vectors(m, s);
	rotate_camera(m);
	m->t.a = (m->t.normalized_direction_x * m->t.normalized_direction_x)
	+ (m->t.normalized_direction_y * m->t.normalized_direction_y)
	+ (m->t.normalized_direction_z * m->t.normalized_direction_z);
	m->t.b = 2 * ((m->t.normalized_direction_x * m->t.distx)
	+ (m->t.normalized_direction_y * m->t.disty)
	+ (m->t.normalized_direction_z * m->t.distz));
	m->t.c = ((m->t.distx * m->t.distx) + (m->t.disty * m->t.disty)
	+ (m->t.distz * m->t.distz))
	- (s->radius * s->radius);
	m->t.t_value = get_t_value(m);
	if (m->t.t_value < 0.0)
		return (-0.000001);
	else
		return (m->t.t_value);
}

double	check_for_cylinder(t_master *m, t_shape *s)
{
	normalize_vectors(m, s);
	rotate_camera(m);
	rotate(m, s);
	inner_product(m);
	m->t.b = 2 * m->t.b;
	m->t.c = m->t.c - (s->radius * s->radius);
	m->t.t_value = get_t_value(m);
	if (m->t.t_value < 0.0)
		return (-0.000001);
	else
		return (m->t.t_value);
}

double	check_for_cone(t_master *m, t_shape *s)
{
	normalize_vectors(m, s);
	rotate_camera(m);
	rotate(m, s);
	inner_product(m);
	m->t.a = (cos(s->radius) * cos(s->radius)) * m->t.a
	- (sin(s->radius) * sin(s->radius)) * (m->t.dot_product * m->t.dot_product);
	m->t.b = 2 * (cos(s->radius) * cos(s->radius)) * m->t.b -
	2 * (sin(s->radius) * sin(s->radius)) * (m->t.dot_product * m->t.p);
	m->t.c = (cos(s->radius) * cos(s->radius))
	* m->t.c - (sin(s->radius) * sin(s->radius)) * (m->t.p * m->t.p);
	m->t.t_value = get_t_value(m);
	if (m->t.t_value < 0.0)
		return (-0.000001);
	else
		return (m->t.t_value);
}

double	check_for_plane(t_master *m, t_shape *s)
{
	normalize_vectors(m, s);
	rotate_camera(m);
	// m->t.distx = s->shape_origin_x - m->c.camera_origin_x;
	// m->t.disty = s->shape_origin_y - m->c.camera_origin_y;
	// m->t.distz = s->shape_origin_z - m->c.camera_origin_z;
	m->t.vax = 0.0;
	m->t.vay = 0.0;
	m->t.vaz = 1.0;
	rotate(m, s);
	m->t.b = (m->t.normalized_direction_x * m->t.vax)
	+ (m->t.normalized_direction_y * m->t.vay)
	+ (m->t.normalized_direction_z * m->t.vaz);
	if (POS(m->t.b) > 0.0)
	{
		m->t.a = (m->t.distx * m->t.vax) + (m->t.disty * m->t.vay)
		+ (m->t.distz * m->t.vaz);
		m->t.t_value = -m->t.a / m->t.b;
		if (m->t.t_value >= 0.0)
			return (m->t.t_value);
	}
		return (-0.000001);
}
