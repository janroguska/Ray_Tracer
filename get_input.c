/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 17:00:24 by jroguszk          #+#    #+#             */
/*   Updated: 2018/03/09 17:00:25 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer.h"

int		read_file(t_master *m, char *argv)
{
	int		i;
	int		j;

	m->r.fd = open(argv, O_RDONLY);
	i = 0;
	if (m->r.fd == -1)
		exit(0);
	while ((m->r.ret = get_next_line(m->r.fd, &m->r.line)) > 0)
	{
		i = 0;
		j = -1;
		if (m->r.ret == -1)
			return (0);
		while (m->r.line[i] != '\t' && m->r.line[i] != ':' &&
			m->r.line[i] != ' ' && m->r.line[i] != '\n' && m->r.line[i] != '\0')
			i++;
		m->r.tmp = ft_strnew(i + 1);
		while (++j < i)
			m->r.tmp[j] = m->r.line[j];
		m->r.tmp[j] = '\0';
		free(m->r.line);
		check_input(m);
	}
	return (0);
}

int		check_input(t_master *m)
{
	if (ft_strcmp("light", m->r.tmp) == 0)
		get_light_coordinates(m);
	if (ft_strcmp("camera", m->r.tmp) == 0)
		get_camera_coordinates(m);
	if (ft_strcmp("object", m->r.tmp) == 0)
		get_object_coordinates(m);
	free(m->r.tmp);
	return (0);
}

void	initialize_light(t_light *l)
{
	l->light_origin_x = 0.0;
	l->light_origin_y = 0.0;
	l->light_origin_z = 0.0;
	l->surface_x = 0.0;
	l->surface_y = 0.0;
	l->surface_z = 0.0;
	l->light_normal_x = 0.0;
	l->light_normal_y = 0.0;
	l->light_normal_z = 0.0;
	l->angle = 0.0;
	l->intensity = 0.0;
	l->ambience = 0.0;
	l->colour = 0.0;
	l->light_to_shape_x = 0.0;
	l->light_to_shape_y = 0.0;
	l->light_to_shape_z = 0.0;
}

void	initialize_coordinates(t_shape *s)
{
	s->shape_id = 0.0;
	s->shape_origin_x = 0.0;
	s->shape_origin_y = 0.0;
	s->shape_origin_z = 0.0;
	s->radius = 0.0;
	s->rotate_shape_x = 0.0;
	s->rotate_shape_y = 0.0;
	s->rotate_shape_z = 0.0;
}
