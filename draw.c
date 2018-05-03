/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 16:28:33 by jroguszk          #+#    #+#             */
/*   Updated: 2018/05/01 16:28:35 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer.h"

int		draw(t_master *m)
{
	t_list	*tmp;

	m->d.z = -WIDTH / 2;
	m->d.y = -1;
	tmp = m->list;
	while (++m->d.y < HEIGHT)
	{
		m->d.x = -1;
		while (++m->d.x < WIDTH)
			check_shape(m, tmp);
	}
	mlx_put_image_to_window(m->e.mlx, m->e.win, m->e.img, 0, 0);
	return (0);
}

void	check_shape(t_master *m, t_list *list)
{
	double		i;
	double		j;
	int			k;
	t_shape		*s;
	t_list		*tmp;

	j = 0.0;
	k = 0;
	tmp = list;
	normalize_vectors(m);
	rotate_camera(m);
	while (tmp != NULL && tmp->content != NULL)
	{
		s = (t_shape*)tmp->content;
		set_variables(m, s);
		i = shoot_ray(m, s);
		if (k++ == 0)
			j = i;
		if (i >= 0 && (i <= j || j < 0))
		{
			j = i;
			colour(m, s, list);
		}
		tmp = tmp->next;
	}
}

void	set_variables(t_master *m, t_shape *s)
{
	m->c.direction_x = m->d.x;
	m->c.direction_y = m->d.y;
	m->c.direction_z = m->d.z;
	m->t.distx = m->c.camera_origin_x - s->shape_origin_x;
	m->t.disty = m->c.camera_origin_y - s->shape_origin_y;
	m->t.distz = m->c.camera_origin_z - s->shape_origin_z;
	m->t.vax = 0.0;
	m->t.vay = 1.0;
	m->t.vaz = 0.0;
}

double	shoot_ray(t_master *m, t_shape *s)
{
	double	i;

	i = -0.000001;
	if (s->shape_id == 0)
		i = check_for_sphere(m, s);
	else if (s->shape_id == 1)
		i = check_for_cylinder(m, s);
	else if (s->shape_id == 2)
		i = check_for_cone(m, s);
	else if (s->shape_id == 3)
		i = check_for_plane(m, s);
	return (i);
}

void	colour(t_master *m, t_shape *s, t_list *list)
{
	double		i;
	t_master	a;

	ft_memcpy(&a, m, sizeof(t_master));
	if ((i = light_check(&a, s, list)) == 0.0)
		a.l.angle = a.l.colour;
	if (s->shape_id == 0.0)
		m->e.addr[ft_round(m->d.x +
		(m->d.y * WIDTH))] = ft_round(a.l.angle) * 256 * 256;
	else if (s->shape_id == 1.0)
		m->e.addr[ft_round(m->d.x +
		(m->d.y * WIDTH))] = ft_round(a.l.angle) * 256;
	else if (s->shape_id == 2.0)
		m->e.addr[ft_round(m->d.x +
		(m->d.y * WIDTH))] = ft_round(a.l.angle);
	else if (s->shape_id == 3.0)
		m->e.addr[ft_round(m->d.x +
		(m->d.y * WIDTH))] = ft_round(a.l.angle) * 256 * 256;
}
