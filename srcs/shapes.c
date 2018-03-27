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
	int		i;

	i = 0;
	rotate_camera(m);
	normalize_vectors(m, s);
	m->t.a = (m->t.nx * m->t.nx) + (m->t.ny * m->t.ny) + (m->t.nz * m->t.nz);
	m->t.b = 2 * ((m->t.nx * m->t.distx) + (m->t.ny * m->t.disty)
	+ (m->t.nz * m->t.distz));
	m->t.c = ((m->t.distx * m->t.distx) + (m->t.disty * m->t.disty)
	+ (m->t.distz * m->t.distz))
	- (s->r * s->r);
	m->t.discr = get_t_value(m);
	if (m->t.discr < 0)
		return (-0.000001);
	else
	{
		if ((i = light_check(m, s)) == 1)
			return (m->t.discr);
		else
			return (-0.000001);
	}
}

double	check_for_cylinder(t_master *m, t_shape *s)
{
	int		i;

	i = 0;
	rotate_camera(m);
	normalize_vectors(m, s);
	rotate(m, s);
	inner_product(m);
	m->t.a = m->t.a;
	m->t.b = 2 * m->t.b;
	m->t.c = m->t.c - (s->r * s->r);
	m->t.discr = get_t_value(m);
	if (m->t.discr < 0)
		return (-0.000001);
	else
	{
		if ((i = light_check(m, s)) == 1)
			return (m->t.discr);
		else
			return (-0.000001);
	}
}

double	check_for_cone(t_master *m, t_shape *s)
{
	int		i;

	i = 0;
	rotate_camera(m);
	normalize_vectors(m, s);
	rotate(m, s);
	inner_product(m);
	m->t.a = (cos(s->r) * cos(s->r)) * m->t.a - (sin(s->r) * sin(s->r)) * (m->t.v * m->t.v);
	m->t.b = 2 * (cos(s->r) * cos(s->r)) * m->t.b - 2 * (sin(s->r) * sin(s->r)) * (m->t.v * m->t.p);
	m->t.c = (cos(s->r) * cos(s->r)) * m->t.c - (sin(s->r) * sin(s->r)) * (m->t.p * m->t.p);
	m->t.discr = get_t_value(m);
	if (m->t.discr < 0)
		return (-0.000001);
	else
	{
		if ((i = light_check(m, s)) == 1)
			return (m->t.discr);
		else
			return (-0.000001);
	}
}

double	check_for_plane(t_master *m, t_shape *s)
{
	int		i;

	i = 0;
	rotate_camera(m);
	normalize_vectors(m, s);
	m->t.distx = s->x - m->c.x;
	m->t.disty = s->y - m->c.y;
	m->t.distz = s->z - m->c.z;
	m->t.vax = 0;
	m->t.vay = 0;
	m->t.vaz = 1;
	rotate(m, s);
	m->t.a = (m->t.distx * m->t.vax) + (m->t.disty * m->t.vay) + (m->t.distz * m->t.vaz);
	m->t.b = (m->t.nx * m->t.vax) + (m->t.ny * m->t.vay) + (m->t.nz * m->t.vaz);
	m->t.discr = m->t.a / m->t.b;
	if (m->t.discr >= 0)
	{
		if ((i = light_check(m, s)) == 1)
			return (m->t.discr);
		else
			return (-0.000001);
	}
	else
		return (-0.000001);
}
