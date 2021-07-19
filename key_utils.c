#include "so_long.h"

void	ft_c(struct s_window *m, int v)
{
	m->map[m->x] = '0';
	m->map[v] = 'P';
	m->x = v;
}

void	ft_w(struct s_window *m, int v)
{
	m->zmienna1 = 1;
	m->map[m->x] = '0';
	m->map[v] = 'P';
}

void	ft_move(struct s_window *m, int v)
{
	m->map[m->x] = m->map[v];
	m->map[v] = 'P';
	m->x = v;
}

void	ft_e(struct s_window *m, int v)
{
	m->zmienna1 = 2;
	m->map[m->x] = '0';
	m->map[v] = 'P';
}	

void	ft_wsad(struct s_window *m, int v)
{
	if (m->map[v] != '1')
	{
		if (m->map[v] == 'C')
			ft_c(m, v);
		else if (m->map[v] == 'W')
			ft_w(m, v);
		else if (m->map[v] == 'E')
			ft_e(m, v);
		else
			ft_move(m, v);
	}
}
