/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_coordinates.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 15:16:36 by jroguszk          #+#    #+#             */
/*   Updated: 2018/05/01 15:16:38 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer.h"

void	get_light_coordinates(t_master *m)
{
	int		i;
	int		j;
	t_list	*tmp;
	t_light	*l;

	i = 0;
	j = -1;
	l = malloc(sizeof(t_light));
	initialize_light(l);
	while (++j <= 4)
	{
		i = 0;
		if ((m->r.ret = get_next_line(m->r.fd, &m->r.line)) < 1)
			return ;
		while (m->r.line[++i] != '\0'
		&& (m->r.line[i] < 48 || m->r.line[i] > 57) && m->r.line[i] != '-')
			allocate_light(m, l, j, i);
		free(m->r.line);
	}
	tmp = ft_lstnew(l, sizeof(t_light));
	ft_lstadd(&m->light, tmp);
	free(l);
}

void	get_camera_coordinates(t_master *m)
{
	int		i;
	int		j;

	j = -1;
	while (++j <= 5)
	{
		i = 0;
		if ((m->r.ret = get_next_line(m->r.fd, &m->r.line)) < 1)
			return ;
		while (m->r.line[++i] != '\0'
		&& (m->r.line[i] < 48 || m->r.line[i] > 57) && m->r.line[i] != '-')
			if (j == 0)
				m->c.camera_origin_x = ft_atof(m->r.line + i);
			else if (j == 1)
				m->c.camera_origin_y = ft_atof(m->r.line + i);
			else if (j == 2)
				m->c.camera_origin_z = ft_atof(m->r.line + i);
			else if (j == 3)
				m->c.rotate_camera_x = ft_atof(m->r.line + i);
			else if (j == 4)
				m->c.rotate_camera_y = ft_atof(m->r.line + i);
			else if (j == 5)
				m->c.rotate_camera_z = ft_atof(m->r.line + i);
		free(m->r.line);
	}
}

void	get_object_coordinates(t_master *m)
{
	int		i;
	int		j;
	t_list	*tmp;
	t_shape	*s;

	i = 0;
	j = -1;
	s = malloc(sizeof(t_shape));
	initialize_coordinates(s);
	while (++j <= 7)
	{
		i = 0;
		if ((m->r.ret = get_next_line(m->r.fd, &m->r.line)) < 1)
			return ;
		while (m->r.line[++i] != '\0'
		&& (m->r.line[i] < 48 || m->r.line[i] > 57) && m->r.line[i] != '-')
			allocate_coordinates(m, s, j, i);
		free(m->r.line);
	}
	tmp = ft_lstnew(s, sizeof(t_shape));
	ft_lstadd(&m->list, tmp);
	free(s);
}

void	allocate_coordinates(t_master *m, t_shape *s, int j, int i)
{
	if (j == 0)
		s->shape_id = ft_atof(m->r.line + i);
	else if (j == 1)
		s->shape_origin_x = ft_atof(m->r.line + i);
	else if (j == 2)
		s->shape_origin_y = ft_atof(m->r.line + i);
	else if (j == 3)
		s->shape_origin_z = ft_atof(m->r.line + i);
	else if (j == 4)
		s->radius = ft_atof(m->r.line + i);
	else if (j == 5)
		s->rotate_shape_x = ft_atof(m->r.line + i);
	else if (j == 6)
		s->rotate_shape_y = ft_atof(m->r.line + i);
	else if (j == 7)
		s->rotate_shape_z = ft_atof(m->r.line + i);
	else
		return ;
}

void	allocate_light(t_master *m, t_light *l, int j, int i)
{
	if (j == 0)
		l->light_origin_x = ft_atof(m->r.line + i);
	else if (j == 1)
		l->light_origin_y = ft_atof(m->r.line + i);
	else if (j == 2)
		l->light_origin_z = ft_atof(m->r.line + i);
	else if (j == 3)
		l->intensity = ft_atof(m->r.line + i);
	else if (j == 4)
		l->ambience = ft_atof(m->r.line + i);
}
