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

double	get_t_value(t_master *m)
{
	double	discr;
	double	sqrtdiscr;
	double	t0;
	double	t1;

	discr = m->t.b * m->t.b - 4 * m->t.a * m->t.c;
	if (discr < 0)
		return (-0.000001);
	else
	{
		sqrtdiscr = sqrt(discr);
		t0 = (-m->t.b + sqrtdiscr) / 2;
		t1 = (-m->t.b - sqrtdiscr) / 2;
		if (t0 < t1 && t0 >= 0)
			return (t0);
		else if (t1 <= t0 && t1 >= 0)
			return (t1);
		else
			return (-0.000001);
	}
}

void	normalize_vectors(t_master *m, t_shape *s)
{
	m->t.len = sqrt((m->d.x * m->d.x) + (m->d.y * m->d.y) + (m->d.z * m->d.z));
	m->t.nx = m->d.x / m->t.len;
	m->t.ny = m->d.y / m->t.len;
	m->t.nz = m->d.z / m->t.len;
	// m->t.distx = s->x - m->c.x;
	// m->t.disty = s->y - m->c.y;
	// m->t.distz = s->z - m->c.z;
	m->t.distx = m->c.x - s->x;
	m->t.disty = m->c.y - s->y;
	m->t.distz = m->c.z - s->z;
	m->t.vax = 0;
	m->t.vay = 1;
	m->t.vaz = 0;
}

double	check_for_sphere(t_master *m, t_shape *s)
{
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
		// printf("sphere: %f\n", m->t.discr);
		return (m->t.discr);
	}
}

void	inner_product(t_master *m)
{
	m->t.v = (m->t.nx * m->t.vax) + (m->t.ny * m->t.vay) + (m->t.nz * m->t.vaz);
	m->t.vx = m->t.nx - (m->t.v * m->t.vax);
	m->t.vy = m->t.ny - (m->t.v * m->t.vay);
	m->t.vz = m->t.nz - (m->t.v * m->t.vaz);
	m->t.p = (m->t.distx * m->t.vax) + (m->t.disty * m->t.vay)
	+ (m->t.distz * m->t.vaz);
	m->t.px = m->t.distx - (m->t.p * m->t.vax);
	m->t.py = m->t.disty - (m->t.p * m->t.vay);
	m->t.pz = m->t.distz - (m->t.p * m->t.vaz);
	m->t.a = (m->t.vx * m->t.vx) + (m->t.vy
	* m->t.vy) + (m->t.vz * m->t.vz);
	m->t.b = ((m->t.vx * m->t.px) + (m->t.vy * m->t.py)
	+ (m->t.vz * m->t.pz));
	m->t.c = ((m->t.px * m->t.px) + (m->t.py * m->t.py)
	+ (m->t.pz * m->t.pz));

}

double	check_for_cylinder(t_master *m, t_shape *s)
{
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
		// printf("cylinder: %f\n", m->t.discr);
		return (m->t.discr);
	}
}

double	check_for_cone(t_master *m, t_shape *s)
{
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
		// printf("cone: %f\n", m->t.discr);
		return (m->t.discr);
	}
}

void	rotate(t_master *m, t_shape *s)
{
	double	x;
	double	y;
	double	z;

	y = (m->t.vay * cos(To_Radians(s->rx))) - (m->t.vaz * sin(To_Radians(s->rx)));
	z = (m->t.vay * sin(To_Radians(s->rx))) + (m->t.vaz * cos(To_Radians(s->rx)));
	x = m->t.vax;
	m->t.vay = y;
	m->t.vaz = z;
	z = (m->t.vaz * cos(To_Radians(s->ry))) - (m->t.vax * sin(To_Radians(s->ry)));
	x = (m->t.vaz * sin(s->ry)) + (m->t.vax * cos(s->ry));
	m->t.vax = x;
	m->t.vaz = z;
	x = (m->t.vax * cos(To_Radians(s->rz))) - (m->t.vay * sin(To_Radians(s->rz)));
	y = (m->t.vax * sin(To_Radians(s->rz))) + (m->t.vay * cos(To_Radians(s->rz)));
	m->t.vax = x;
	m->t.vay = y;
}

double	check_for_plane(t_master *m, t_shape *s)
{
	normalize_vectors(m, s);
	// m->t.distx = m->c.x - s->x;
	// m->t.disty = m->c.y - s->y;
	// m->t.distz = m->c.z - s->z;
	rotate(m, s);
	m->t.a = (m->t.distx * m->t.vax) + (m->t.disty * m->t.vay) + (m->t.distz * m->t.vaz);
	m->t.b = (m->t.nx * m->t.vax) + (m->t.ny * m->t.vay) + (m->t.nz * m->t.vaz);
	m->t.discr = m->t.a / m->t.b;
	if (m->t.discr >= 0)
	{
		// printf("cylinder: %f\n", m->t.discr);
		return (m->t.discr);
	}
	else
		return (-0.000001);
}