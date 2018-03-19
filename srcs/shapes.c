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

int		check_for_sphere(t_master *m, t_shape *s)
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
		return (0);
	else
		return (1);

}

// int		check_for_cylinder(t_master *m, t_shape *s)
// {
// 	m->t.distx = m->c.x - s->x;
// 	m->t.disty = m->c.y - s->y;
// 	m->t.distz = m->c.z - s->z;
// 	m->t.a = (m->d.x * m->d.x) + (m->d.z * m->d.z);
// 	m->t.b = 2 * ((m->d.x * m->t.distx) + (m->d.z * m->t.distz));
// 	m->t.c = ((m->t.distx * m->t.distx) + (m->t.distz * m->t.distz))
// 	- (s->r * s->r);
// 	m->t.discr = m->t.b * m->t.b - 4 * m->t.a * m->t.c;
// 	m->t.discrsq = sqrt(m->t.discr);
// 	m->t.t0 = (-m->t.b + m->t.discrsq) / (2 * m->t.a);
// 	m->t.t1 = (-m->t.b - m->t.discrsq) / (2 * m->t.a);
// 	if (m->t.t0 > m->t.t1)
// 		ft_swap_double(&m->t.t0, &m->t.t1);
// 	m->t.y0 = m->t.disty + m->t.t0 * m->d.y;
// 	m->t.y1 = m->t.disty + m->t.t1 * m->d.y;
// 	if (m->t.discr < 0)
// 		return (0);
// 	else
// 		return (cylinder_intersection(m));
// }

int		check_for_cylinder(t_master *m, t_shape *s)
{
	m->t.distx = m->c.x - s->x;
	m->t.disty = m->c.y - s->y;
	m->t.distz = m->c.z - s->z;
	m->t.vax = 0;
	m->t.vay = 1;
	m->t.vaz = 0;
	rotate(m, s);
	m->t.v = (m->d.x * m->t.vax) + (m->d.y * m->t.vay) + (m->d.z * m->t.vaz);
	m->t.vx = m->t.v * m->t.vax;
	m->t.vy = m->t.v * m->t.vay;
	m->t.vz = m->t.v * m->t.vaz;
	m->t.a = ((m->d.x - m->t.vx) * (m->d.x - m->t.vx)) + ((m->d.y - m->t.vy)
	* (m->d.y - m->t.vy)) + ((m->d.z - m->t.vz) * (m->d.z - m->t.vz));
	m->t.p = (m->t.distx * m->t.vax) + (m->t.vay * m->t.vay) + (m->t.distz * m->t.vaz);
	m->t.px = m->t.distx - (m->t.p * m->t.vax);
	m->t.py = m->t.disty - (m->t.p * m->t.vay);
	m->t.pz = m->t.distz - (m->t.p * m->t.vaz);
	m->t.b = 2 * (((m->d.x - m->t.vx) * m->t.px) + ((m->d.y - m->t.vy) * m->t.py) + ((m->d.z - m->t.vz) * m->t.pz));
	m->t.c = ((m->t.px + m->t.py + m->t.pz) * (m->t.px + m->t.py + m->t.pz)) - (s->r * s->r);
	m->t.discr = m->t.b * m->t.b - 4 * m->t.a * m->t.c;
	m->t.discrsq = sqrt(m->t.discr);
	m->t.t0 = (-m->t.b + m->t.discrsq) / (2 * m->t.a);
	m->t.t1 = (-m->t.b - m->t.discrsq) / (2 * m->t.a);
	if (m->t.t0 > m->t.t1)
		ft_swap_double(&m->t.t0, &m->t.t1);
	m->t.y0 = m->t.disty + m->t.t0 * m->d.y;
	m->t.y1 = m->t.disty + m->t.t1 * m->d.y;
	if (m->t.discr < 0)
		return (0);
	else
		return (cylinder_intersection(m));
}

int		cylinder_intersection(t_master *m)
{
	// if (m->t.y0 < -1)
	// {
	// 	if (m->t.y1 < -1)
	// 		return (0);
	// 	if ((m->t.th = m->t.t0 + (m->t.t1 - m->t.t0) * (m->t.y0 + 1)
	// 		/ (m->t.y0 - m->t.y1)) <= 0)
	// 		return (0);
	// 	return (1);
	// }
	// else if (m->t.y0 >= -1 && m->t.y0 <= 1)
	// {
		if (m->t.t0 <= 0)
			return (0);
		return (1);
	// }
	// else if (m->t.y0 > 1)
	// {
	// 	if (m->t.y1 > 1)
	// 		return (0);
	// 	if ((m->t.th = m->t.t0 + (m->t.t1 - m->t.t0) * (m->t.y0 - 1)
	// 		/ (m->t.y0 - m->t.y1)) <= 0)
	// 		return (0);
	// 	return (1);
	// }
	// return (0);
}

int		check_for_cone(t_master *m, t_shape *s)
{
	m->t.distx = m->c.x - s->x;
	m->t.disty = m->c.y - s->y;
	m->t.distz = m->c.z - s->z;
	m->t.a = (m->d.y * m->d.y) + (m->d.z * m->d.z) - (m->d.x * m->d.x);
	m->t.b = 2 * ((m->d.y * m->t.disty) + (m->d.z * m->t.distz)
	- (m->d.x * m->t.distx));
	m->t.c = ((m->t.disty * m->t.disty) + (m->t.distz * m->t.distz)
	- (m->t.distx * m->t.distx))
	- (s->r * s->r);
	m->t.discr = m->t.b * m->t.b - 4 * m->t.a * m->t.c;
	if (m->t.discr < 0)
		return (0);
	else
		return (1);

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

// int		check_for_plane(t_master *m, t_shape *s)
// {

// }