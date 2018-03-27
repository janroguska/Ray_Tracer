/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_arithmetic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 10:10:06 by jroguszk          #+#    #+#             */
/*   Updated: 2018/03/26 10:10:23 by jroguszk         ###   ########.fr       */
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
	m->t.len = sqrt((m->c.dx * m->c.dx) + (m->c.dy * m->c.dy) + (m->c.dz * m->c.dz));
	m->t.nx = m->c.dx / m->t.len;
	m->t.ny = m->c.dy / m->t.len;
	m->t.nz = m->c.dz / m->t.len;
	m->t.distx = m->c.x - s->x;
	m->t.disty = m->c.y - s->y;
	m->t.distz = m->c.z - s->z;
	m->t.vax = 0;
	m->t.vay = 1;
	m->t.vaz = 0;
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
	x = (m->t.vaz * sin(To_Radians(s->ry))) + (m->t.vax * cos(To_Radians(s->ry)));
	m->t.vax = x;
	m->t.vaz = z;
	x = (m->t.vax * cos(To_Radians(s->rz))) - (m->t.vay * sin(To_Radians(s->rz)));
	y = (m->t.vax * sin(To_Radians(s->rz))) + (m->t.vay * cos(To_Radians(s->rz)));
	m->t.vax = x;
	m->t.vay = y;
}

void	rotate_camera(t_master *m)
{
	double	x;
	double	y;
	double	z;

	m->c.dx = m->d.x;
	m->c.dy = m->d.y;
	m->c.dz = m->d.z;
	y = (m->c.dy * cos(To_Radians(m->c.rx))) - (m->c.dz * sin(To_Radians(m->c.rx)));
	z = (m->c.dy * sin(To_Radians(m->c.rx))) + (m->c.dz * cos(To_Radians(m->c.rx)));
	x = m->c.dx;
	m->c.dy = y;
	m->c.dz = z;
	z = (m->c.dz * cos(To_Radians(m->c.ry))) - (m->c.dx * sin(To_Radians(m->c.ry)));
	x = (m->c.dz * sin(To_Radians(m->c.ry))) + (m->c.dx * cos(To_Radians(m->c.ry)));
	m->c.dx = x;
	m->c.dz = z;
	x = (m->c.dx * cos(To_Radians(m->c.rz))) - (m->c.dy * sin(To_Radians(m->c.rz)));
	y = (m->c.dx * sin(To_Radians(m->c.rz))) + (m->c.dy * cos(To_Radians(m->c.rz)));
	m->c.dx = x;
	m->c.dy = y;
}
