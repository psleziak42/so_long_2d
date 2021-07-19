#include "so_long.h"

void	ft_struct_init(struct s_window *m)
{
	m->w_x = 0;
	m->w_y = 0;
	m->h_j = -1;
}

int	main(int argv, char **argc)
{
	struct s_window	m;

	if (argv != 2)
		return (0);
	if (!ft_get_ready(&m, argc[1]))
	{
		perror("Preprocess Error");
		exit(1);
	}
	if (!ft_check_de_map(&m))
	{
		perror("Map Error");
		exit(1);
	}
	m.mlx_p = mlx_init();
	m.w_p = mlx_new_window(m.mlx_p, m.s_w_x, m.s_w_y, "PoK3M0Ny");
	mlx_key_hook(m.w_p, deal_key, &m);
	mlx_hook(m.w_p, 17, 1L << 0, close_window, &m);
	if (!ft_landscape(&m) || !map_create(&m))
	{
		perror("Image adress Error");
		exit(1);
	}
	mlx_loop(m.mlx_p);
}
