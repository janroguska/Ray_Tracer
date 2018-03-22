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
	m->t.distx = m->c.x - s->x;
	m->t.disty = m->c.y - s->y;
	m->t.distz = m->c.z - s->z;
	m->t.a = (m->d.x * m->d.x) + (m->d.y * m->d.y) + (m->d.z * m->d.z);
	m->t.b = 2 * ((m->d.x * m->t.distx) + (m->d.y * m->t.disty)
	+ (m->d.z * m->t.distz));
	m->t.c = ((m->t.distx * m->t.distx) + (m->t.disty * m->t.disty)
	+ (m->t.distz * m->t.distz))
	- (s->r * s->r);
	m->t.discr = m->t.b * m->t.b - 4 * m->t.a * m->t.c;
	if (m->t.discr < 0)
		return (-0.000001);
	else
		return (m->t.discr);
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
	m->t.len = sqrt((m->d.x * m->d.x) + (m->d.y * m->d.y) + (m->d.z * m->d.z));
	m->t.nx = m->d.x / m->t.len;
	m->t.ny = m->d.y / m->t.len;
	m->t.nz = m->d.z / m->t.len;
	m->t.distx = m->c.x - s->x;
	m->t.disty = m->c.y - s->y;
	m->t.distz = m->c.z - s->z;
	m->t.vax = 0;
	m->t.vay = 1;
	m->t.vaz = 0;
	rotate(m, s);
	inner_product(m);
	m->t.a = m->t.a;
	m->t.b = 2 * m->t.b;
	m->t.c = m->t.c - (s->r * s->r);
	m->t.discr = m->t.b * m->t.b - 4 * m->t.a * m->t.c;
	if (m->t.discr < 0)
		return (-0.000001);
	else
		return (m->t.discr);
}

double	check_for_cone(t_master *m, t_shape *s)
{
	m->t.len = sqrt((m->d.x * m->d.x) + (m->d.y * m->d.y) + (m->d.z * m->d.z));
	m->t.nx = m->d.x / m->t.len;
	m->t.ny = m->d.y / m->t.len;
	m->t.nz = m->d.z / m->t.len;
	m->t.distx = m->c.x - s->x;
	m->t.disty = m->c.y - s->y;
	m->t.distz = m->c.z - s->z;
	m->t.vax = 0;
	m->t.vay = 1;
	m->t.vaz = 0;
	rotate(m, s);
	inner_product(m);
	m->t.a = (cos(s->r) * cos(s->r)) * m->t.a - (sin(s->r) * sin(s->r)) * (m->t.v * m->t.v);
	m->t.b = 2 * (cos(s->r) * cos(s->r)) * m->t.b - 2 * (sin(s->r) * sin(s->r)) * (m->t.v * m->t.p);
	m->t.c = (cos(s->r) * cos(s->r)) * m->t.c - (sin(s->r) * sin(s->r)) * (m->t.p * m->t.p);
	m->t.discr = m->t.b * m->t.b - 4 * m->t.a * m->t.c;
	if (m->t.discr < 0)
		return (-0.000001);
	else
		return (m->t.discr);
}

void	rotate(t_master *m, t_shape *s)
{
	double	x;
	double	y;
	double	z;

	y = (m->t.vay * cos(s->rx)) - (m->t.vaz * sin(s->rx));
	z = (m->t.vay * sin(s->rx)) + (m->t.vaz * cos(s->rx));
	x = m->t.vax;
	m->t.vay = y;
	m->t.vaz = z;
	z = (m->t.vaz * cos(s->ry)) - (m->t.vax * sin(s->ry));
	x = (m->t.vaz * sin(s->ry)) + (m->t.vax * cos(s->ry));
	m->t.vax = x;
	m->t.vaz = z;
	x = (m->t.vax * cos(s->rz)) - (m->t.vay * sin(s->rz));
	y = (m->t.vax * sin(s->rz)) + (m->t.vay * cos(s->rz));
	m->t.vax = x;
	m->t.vay = y;
}

double	check_for_plane(t_master *m, t_shape *s)
{
	m->t.len = sqrt((m->d.x * m->d.x) + (m->d.y * m->d.y) + (m->d.z * m->d.z));
	m->t.nx = m->d.x / m->t.len;
	m->t.ny = m->d.y / m->t.len;
	m->t.nz = m->d.z / m->t.len;
	m->t.distx = s->x - m->c.x;
	m->t.disty = s->y - m->c.y;
	m->t.distz = s->z - m->c.z;
	m->t.vax = 0;
	m->t.vay = 1;
	m->t.vaz = 0;
	rotate(m, s);
	inner_product(m);
	m->t.a = (m->t.distx * m->t.vax) + (m->t.disty * m->t.vay) + (m->t.distz * m->t.vaz);
	m->t.b = (m->t.nx * m->t.vax) + (m->t.ny * m->t.vay) + (m->t.nz * m->t.vaz);
	m->t.discr = m->t.a / m->t.b;
	if (m->t.discr >= 0)
		return (m->t.discr);
	else
		return (-0.000001);
}