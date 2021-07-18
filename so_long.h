#ifndef SO_LONG_H
# define SO_LONG_H
#include "./libft/libft.h"
#include "./gnl/get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define ESC 53
#define a	0
#define	s	1
#define	w	13
#define	d	2

struct s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_instance;
	void	*img_night;
	char	*adres;
	char	*filename;
	char	*line;
	char	**map;
	char	*map;
	int		string;
	int		s_w_x;
	int		s_w_y;
	int		w_x;
	int		w_y;
	int		i_h;
	int		i_w;
	int		h_i;
	int		h_j;
	int		h_l;
	int		h_k;
	int		h_u;
	int		h_t;
	int		color;
	int		c_t;
	int		c_r;
	int		c_g;
	int		c_b;
	int		key_pressed;
	int		map_counter;
	int		fd;
	int		zmienna1;
};



#endif
