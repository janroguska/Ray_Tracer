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
	if (discr < 0.0)
		return (-0.000001);
	else if (discr == 0)
		return ((t0 = t_is_zero(m)));
	else
	{
		sqrtdiscr = sqrt(discr);
		if (m->t.a == 0.0)
			return (-0.000001);
		t0 = (-m->t.b + sqrtdiscr) / (2 * m->t.a);
		t1 = (-m->t.b - sqrtdiscr) / (2 * m->t.a);
		if ((t0 < t1 && t0 >= 0) || t1 < 0)
			return (t0);
		else if ((t1 <= t0 && t1 >= 0) || t0 < 0)
			return (t1);
		else
			return (-0.000001);
	}
}

double	t_is_zero(t_master *m)
{
	double	t0;

	t0 = 0.0;
	if (m->t.a == 0.0)
		return (-0.000001);
	t0 = -m->t.b / (2 * m->t.a);
	if (t0 < 0.0)
		return (-0.000001);
	else
		return (t0);
}

void	normalize_vectors(t_master *m)
{
	double	dir_minus_origin_x;
	double	dir_minus_origin_y;
	double	dir_minus_origin_z;

	dir_minus_origin_x = m->c.direction_x - m->c.camera_origin_x;
	dir_minus_origin_y = m->c.direction_y - m->c.camera_origin_y;
	dir_minus_origin_z = m->c.direction_z - m->c.camera_origin_z;
	m->t.ray_length = sqrt((dir_minus_origin_x * dir_minus_origin_x)
	+ (dir_minus_origin_y * dir_minus_origin_y)
	+ (dir_minus_origin_z * dir_minus_origin_z));
	if (m->t.ray_length != 0.0)
	{
		m->t.normalized_direction_x = dir_minus_origin_x / m->t.ray_length;
		m->t.normalized_direction_y = dir_minus_origin_y / m->t.ray_length;
		m->t.normalized_direction_z = dir_minus_origin_z / m->t.ray_length;
	}
	else
	{
		m->t.normalized_direction_x = 0.0;
		m->t.normalized_direction_y = 0.0;
		m->t.normalized_direction_z = 0.0;
	}
}

void	inner_product(t_master *m)
{
	m->t.dot_product = m->t.normalized_direction_x * m->t.vax
	+ m->t.normalized_direction_y * m->t.vay
	+ m->t.normalized_direction_z * m->t.vaz;
	m->t.vx = m->t.normalized_direction_x - (m->t.dot_product * m->t.vax);
	m->t.vy = m->t.normalized_direction_y - (m->t.dot_product * m->t.vay);
	m->t.vz = m->t.normalized_direction_z - (m->t.dot_product * m->t.vaz);
	m->t.p = (m->t.distx * m->t.vax) + (m->t.disty * m->t.vay)
	+ (m->t.distz * m->t.vaz);
	m->t.px = m->t.distx - (m->t.p * m->t.vax);
	m->t.py = m->t.disty - (m->t.p * m->t.vay);
	m->t.pz = m->t.distz - (m->t.p * m->t.vaz);
	m->t.a = (m->t.vx * m->t.vx) + (m->t.vy
	* m->t.vy) + (m->t.vz * m->t.vz);
	m->t.b = (m->t.vx * m->t.px) + (m->t.vy * m->t.py)
	+ (m->t.vz * m->t.pz);
	m->t.c = (m->t.px * m->t.px) + (m->t.py * m->t.py)
	+ (m->t.pz * m->t.pz);
}
