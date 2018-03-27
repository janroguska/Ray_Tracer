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

	m->l.px = m->t.nx * m->t.discr;
	m->l.py = m->t.ny * m->t.discr;
	m->l.pz = m->t.nz * m->t.discr;
	m->l.nx = m->l.px - s->x;
	m->l.ny = m->l.py - s->y;
	m->l.nz = m->l.pz - s->z;
	len = sqrt((m->l.nx * m->l.nx) + (m->l.ny * m->l.ny) + (m->l.nz * m->l.nz));
	m->l.nx /= len;
	m->l.ny /= len;
	m->l.nz /= len;
	get_angle(m, len);
	// printf("%f\n", m->l.angle);
}

void	get_angle(t_master *m, double len)
{
	double	dot;

	dot = (m->t.nx * m->l.nx) + (m->t.ny * m->l.ny) + (m->t.nz * m->l.nz);
	m->l.angle = cos(dot / (m->t.discr * len));
}

int		light_check(t_master *m, t_shape *s)
{
	t_master	a;
	double		i;
	double		j;
	double		k;
	double		l;

	compute_ray_normal(m, s);
	ft_memcpy(&a, m, sizeof(m));
	a.c.x = m->l.px;
	a.c.y = m->l.py;
	a.c.z = m->l.pz;
	a.d.x = 1000;
	a.d.y = 1000;
	a.d.z = 0;
	i = check_for_sphere(&a, s);
	j = check_for_cylinder(&a, s);
	k = check_for_cone(&a, s);
	l = check_for_plane(&a, s);
	if (i < 0 && j < 0 && k < 0 && l < 0)
		return (1);
	else
		return (0);
}
