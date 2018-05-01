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

	m.list = ft_lstnew(NULL, 0);
	m.e.resolution = 1.0;
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

int		key_hook(int keycode)
{
	if (keycode == ESC)
		exit(0);
	return (0);
}

void	ft_clear(t_master *m)
{
	int		i;
	int		j;

	i = 0;
	j = HEIGHT * WIDTH;
	while (i < j)
	{
		m->e.addr[i] = 0x000000;
		i++;
	}
}
