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
		while (m->r.line[i] != '\0' && (m->r.line[i] < 48 || m->r.line[i] > 57) && m->r.line[i] != '-')
			i++;
		allocate_light(m, l, j, i);
		free(m->r.line);
	}
	tmp = ft_lstnew(l, sizeof(t_light));
	ft_lstadd(&m->light, tmp);
	free(l);
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
		while (m->r.line[i] != '\0' && (m->r.line[i] < 48 || m->r.line[i] > 57) && m->r.line[i] != '-')
			i++;
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
		while (m->r.line[i] != '\0' && (m->r.line[i] < 48 || m->r.line[i] > 57) && m->r.line[i] != '-')
			i++;
		allocate_coordinates(m, s, j, i);
		free(m->r.line);
	}
	tmp = ft_lstnew(s, sizeof(t_shape));
	ft_lstadd(&m->list, tmp);
	free(s);
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
