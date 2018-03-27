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
		{
			m->r.tmp[j] = m->r.line[j];
		}
		m->r.tmp[j] = '\0';
		free(m->r.line);
		check_input(m);
	}
	return (0);
}

int		check_input(t_master *m)
{
	if (ft_strcmp("camera", m->r.tmp) == 0)
		get_camera_coordinates(m);
	if (ft_strcmp("object", m->r.tmp) == 0)
		get_object_coordinates(m);
	free(m->r.tmp);
	return (0);
}

int		get_camera_coordinates(t_master *m)
{
	int		i;
	int		j;

	j = -1;
	while (++j <= 5)
	{
		i = 0;
		if ((m->r.ret = get_next_line(m->r.fd, &m->r.line)) < 1)
			return (0);
		while (m->r.line[i] != '\0' && (m->r.line[i] < 48 || m->r.line[i] > 57))
			i++;
		if (j == 0)
			m->c.x = ft_atof(m->r.line + i);
		else if (j == 1)
			m->c.y = ft_atof(m->r.line + i);
		else if (j == 2)
			m->c.z = ft_atof(m->r.line + i);
		else if (j == 3)
			m->c.rx = ft_atof(m->r.line + i);
		else if (j == 4)
			m->c.ry = ft_atof(m->r.line + i);
		else if (j == 5)
			m->c.rz = ft_atof(m->r.line + i);
		free(m->r.line);
	}
	return (0);
}

int		get_object_coordinates(t_master *m)
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
			return (0);
		while (m->r.line[i] != '\0' && (m->r.line[i] < 48 || m->r.line[i] > 57))
			i++;
		allocate_coordinates(m, s, j, i);
		free(m->r.line);
	}
	tmp = ft_lstnew(s, sizeof(t_shape));
	ft_lstadd(&m->list, tmp);
	free(s);
	return (0);
}

void	initialize_coordinates(t_shape *s)
{
	s->s = 0.0;
	s->x = 0.0;
	s->y = 0.0;
	s->z = 0.0;
	s->r = 0.0;
	s->rx = 0.0;
	s->ry = 0.0;
	s->rz = 0.0;
}

void	allocate_coordinates(t_master *m, t_shape *s, int j, int i)
{
	if (j == 0)
		s->s = ft_atof(m->r.line + i);
	else if (j == 1)
		s->x = ft_atof(m->r.line + i);
	else if (j == 2)
		s->y = ft_atof(m->r.line + i);
	else if (j == 3)
		s->z = ft_atof(m->r.line + i);
	else if (j == 4)
		s->r = ft_atof(m->r.line + i);
	else if (j == 5)
		s->rx = ft_atof(m->r.line + i);
	else if (j == 6)
		s->ry = ft_atof(m->r.line + i);
	else if (j == 7)
		s->rz = ft_atof(m->r.line + i);
	else
		return ;
}
