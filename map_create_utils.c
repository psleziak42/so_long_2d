#include "so_long.h"

void	ft_grass(struct s_window *m)
{
	m->f = "img/grass.xpm";
	m->i_i = mlx_xpm_file_to_image(m->mlx_p, m->f, &m->i_h, &m->i_w);
	mlx_put_image_to_window(m->mlx_p, m->w_p, m->i_i, m->w_x, m->w_y);
}

void	ft_img_c(struct s_window *m)
{
	ft_grass(m);
	if (m->map_c % 4 == 0)
		m->f = "img/coin-4.xpm";
	else if (m->map_c % 3 == 0)
		m->f = "img/coin-3.xpm";
	else if (m->map_c % 2 == 0)
		m->f = "img/coin-2.xpm";
	else
		m->f = "img/coin-1.xpm";
}

void	ft_img_w(struct s_window *m)
{
	ft_grass(m);
	if (m->map_c % 4 == 0)
		m->f = "img/4.xpm";
	else if (m->map_c % 3 == 0)
		m->f = "img/3.xpm";
	else if (m->map_c % 2 == 0)
		m->f = "img/2.xpm";
	else
		m->f = "img/1.xpm";
}

void	ft_img_p(struct s_window *m)
{
	if (m->zmienna1 == 1)
	{
		ft_grass(m);
		m->f = "img/ghost.xpm";
	}
	else if (m->zmienna1 == 2)
	{
		ft_grass(m);
		m->f = "img/charmander.xpm";
	}
	else
		m->f = "img/krzew.xpm";
}

void	ft_img_e(struct s_window *m)
{
	if (m->zmienna1 != 2)
		m->f = "img/wood.xpm";
	else
		m->f = "img/grass.xpm";
}
