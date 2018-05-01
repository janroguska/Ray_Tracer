/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 15:35:15 by jroguszk          #+#    #+#             */
/*   Updated: 2018/05/01 15:35:17 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer.h"

void	rotate(t_master *m, t_shape *s)
{
	double	x;
	double	y;
	double	z;

	y = (m->t.vay * cos(RAD(s->rotate_shape_x)))
	- (m->t.vaz * sin(RAD(s->rotate_shape_x)));
	z = (m->t.vay * sin(RAD(s->rotate_shape_x)))
	+ (m->t.vaz * cos(RAD(s->rotate_shape_x)));
	x = m->t.vax;
	m->t.vay = y;
	m->t.vaz = z;
	z = (m->t.vaz * cos(RAD(s->rotate_shape_y)))
	- (m->t.vax * sin(RAD(s->rotate_shape_y)));
	x = (m->t.vaz * sin(RAD(s->rotate_shape_y)))
	+ (m->t.vax * cos(RAD(s->rotate_shape_y)));
	m->t.vax = x;
	m->t.vaz = z;
	x = (m->t.vax * cos(RAD(s->rotate_shape_z)))
	- (m->t.vay * sin(RAD(s->rotate_shape_z)));
	y = (m->t.vax * sin(RAD(s->rotate_shape_z)))
	+ (m->t.vay * cos(RAD(s->rotate_shape_z)));
	m->t.vax = x;
	m->t.vay = y;
}

void	rotate_camera(t_master *m)
{
	double	x;
	double	y;
	double	z;

	y = (m->t.normalized_direction_y * cos(RAD(m->c.rotate_camera_x)))
	- (m->t.normalized_direction_z * sin(RAD(m->c.rotate_camera_x)));
	z = (m->t.normalized_direction_y * sin(RAD(m->c.rotate_camera_x)))
	+ (m->t.normalized_direction_z * cos(RAD(m->c.rotate_camera_x)));
	x = m->t.normalized_direction_x;
	m->t.normalized_direction_y = y;
	m->t.normalized_direction_z = z;
	z = (m->t.normalized_direction_z * cos(RAD(m->c.rotate_camera_y)))
	- (m->t.normalized_direction_x * sin(RAD(m->c.rotate_camera_y)));
	x = (m->t.normalized_direction_z * sin(RAD(m->c.rotate_camera_y)))
	+ (m->t.normalized_direction_x * cos(RAD(m->c.rotate_camera_y)));
	m->t.normalized_direction_x = x;
	m->t.normalized_direction_z = z;
	x = (m->t.normalized_direction_x * cos(RAD(m->c.rotate_camera_z)))
	- (m->t.normalized_direction_y * sin(RAD(m->c.rotate_camera_z)));
	y = (m->t.normalized_direction_x * sin(RAD(m->c.rotate_camera_z)))
	+ (m->t.normalized_direction_y * cos(RAD(m->c.rotate_camera_z)));
	m->t.normalized_direction_x = x;
	m->t.normalized_direction_y = y;
}
