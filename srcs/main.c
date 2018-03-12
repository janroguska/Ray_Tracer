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

int		check_for_sphere(t_master *m)
{
	double	a;
	double	b;
	double	c;

	m->s.distx = m->c.x - m->s.x;
	m->s.disty = m->c.y - m->s.y;
	m->s.distz = m->c.z - m->s.z;
	a = (m->d.x * m->d.x) + (m->d.y * m->d.y) + (m->d.z * m->d.z);
	b = 2 * ((m->d.x * m->s.distx) + (m->d.y * m->s.disty)
	+ (m->d.z * m->s.distz));
	c = ((m->s.distx * m->s.distx) + (m->s.disty * m->s.disty)
	+ (m->s.distz * m->s.distz))
	- (m->s.r * m->s.r);
	m->s.discr = b * b - 4 * a * c;
	if (m->s.discr < 0)
		return (0);
	else
		return (1);
}

int		draw(t_master *m)
{
	double	i;

	m->d.y = -1;
	m->d.z = WIDTH - m->c.z;
	while (++m->d.y < HEIGHT)
	{
		m->d.x = -1;
		while (++m->d.x < WIDTH)
		{
			i = check_for_sphere(m);
			if (i == 1)
				m->e.addr[ft_round(m->d.x + (m->d.y * WIDTH))] = 0xff0000;
			else
				m->e.addr[ft_round(m->d.x + (m->d.y * WIDTH))] = 0x000000;
		}
	}
	mlx_put_image_to_window(m->e.mlx, m->e.win, m->e.img, 0, 0);
	return (0);
}

int		key_hook(int keycode)
{
	if (keycode == ESC)
		exit(0);
	return (0);
}
