/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroguszk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:06:10 by jroguszk          #+#    #+#             */
/*   Updated: 2018/03/05 17:06:35 by jroguszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer.h"

int		main(int argc, char **argv)
{
	t_master	m;

	m.i = 0;
	m.list = ft_lstnew(NULL, 0);
	if (argc != 2)
		return (0);
	m.e.mlx = mlx_init();
	m.e.win = mlx_new_window(m.e.mlx, WIDTH, HEIGHT, "RAYYYYY!!!");
	m.e.img = mlx_new_image(m.e.mlx, WIDTH, HEIGHT);
	m.e.addr = (int*)mlx_get_data_addr(m.e.img, &m.e.bits,
		&m.e.sizeline, &m.e.endian);
	read_file(&m, argv[1]);
	draw(&m);
	mlx_key_hook(m.e.win, key_hook, &m);
	mlx_put_image_to_window(m.e.mlx, m.e.win, m.e.img, 0, 0);
	mlx_loop(m.e.mlx);
	return (0);
}

int		ft_round(double i)
{
	return (i < 0 ? i - 0.5 : i + 0.5);
}

int		draw(t_master *m)
{
	t_list	*tmp;

	m->d.z = m->c.z * -1;
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
	double	i;
	double	j;
	int		k;
	t_shape *s;
	t_list	*tmp;

	i = 0.0;
	j = 0.0;
	k = 0;
	tmp = list;
	while (tmp != NULL && tmp->content != NULL)
	{
		s = (t_shape*)tmp->content;
		if (s->s == 0)
			i = check_for_sphere(m, s);
		else if (s->s == 1)
			i = check_for_cylinder(m, s);
		else if (s->s == 2)
			i = check_for_cone(m, s);
		else if (s->s == 3)
			i = check_for_plane(m, s);
		if (k == 0)
			j = i;
		if (i >= 0 && (i <= j || j < 0))
		{
			j = i;
			colour(m, s);
		}
		tmp = tmp->next;
		k++;                                                                                                                  
	}
}

int		key_hook(int keycode)
{
	if (keycode == ESC)
		exit(0);
	return (0);
}

void	colour(t_master *m, t_shape *s)
{
	if (s->s == 0.0)
		m->e.addr[ft_round(m->d.x + (m->d.y * WIDTH))] = 0xff0000;
	else if (s->s == 1.0)
		m->e.addr[ft_round(m->d.x + (m->d.y * WIDTH))] = 0x00ff00;
	else if (s->s == 2.0)
		m->e.addr[ft_round(m->d.x + (m->d.y * WIDTH))] = 0x0000ff;
	else if (s->s == 3.0)
		m->e.addr[ft_round(m->d.x + (m->d.y * WIDTH))] = 0xffffff;
}
