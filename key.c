#include "so_long.h"

int	close_window(struct s_window *m)
{
	mlx_destroy_window(m->mlx_p, m->w_p);
	exit(1);
}

void	ft_check_zmienna(struct s_window *m)
{
	m->h_j = 0;
	if (m->zmienna1 == 2)
	{
		m->h_j = 0;
		while (m->map[m->h_j] != 'C' && m->map[m->h_j])
			m->h_j++;
		if (m->h_j == m->h_i)
			m->zmienna1 = 2;
		else
			m->zmienna1 = 1;
	}
	map_create(m);
	if (m->zmienna1 == 1)
		mlx_string_put(m->mlx_p, m->w_p, m->s_w_x / 2, m->s_w_y / 2, R, "LOST");
	else if (m->zmienna1 == 2)
		mlx_string_put(m->mlx_p, m->w_p, m->s_w_x / 2, m->s_w_y / 2, G, "WON");
	mlx_string_put(m->mlx_p, m->w_p, m->s_w_x - 55, 32, B, ft_itoa(m->map_c));
}

int	deal_key(int key, struct s_window *m)
{
	m->h_j = 0;
	if (key == ESC)
	{
		mlx_destroy_window(m->mlx_p, m->w_p);
		exit(1);
	}
	if (m->zmienna1)
		return (0);
	while (m->map[m->x] != 'P')
		m->x++;
	if (key == S)
		m->h_j = m->x + m->h_u;
	else if (key == W)
		m->h_j = m->x - m->h_u;
	else if (key == A)
		m->h_j = m->x - 1;
	else if (key == D)
		m->h_j = m->x + 1;
	ft_wsad(m, m->h_j);
	if (key == W || key == S || key == A || key == D)
		ft_putnbr_fd(m->map_c++, 1);
	if (m->map_c >= m->h_i / 5)
		m->zmienna1 = 1;
	ft_check_zmienna(m);
	return (1);
}
