#ifndef SO_LONG_H
# define SO_LONG_H
# include "mlx.h"
# include "./libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# define ESC 53
# define X	17
# define F 	3
# define A	0
# define S	1
# define W	13
# define D	2
# define E	0b01000000
# define C	0b00100000
# define P	0b00010000
# define Z	0b00000000
# define V 	0b00000001
# define G	0x0000FF00
# define R	0x00FF0000
# define B	0x00000000

struct s_window
{
	void	*mlx_p;
	void	*w_p;
	void	*i_i;
	char	*f;
	char	*line;
	char	*map;
	int		s_w_x;
	int		s_w_y;
	int		w_x;
	int		w_y;
	int		i_h;
	int		i_w;
	int		h_i;
	int		h_j;
	int		h_u;
	int		h_t;
	int		x;
	int		key_pressed;
	int		map_c;
	int		fd;
	int		zmienna1;
	char	ECP;
};

int		get_next_line(int fd, char **line);
void	ft_image(struct s_window *m);
void	ft_img_c(struct s_window *m);
void	ft_img_w(struct s_window *m);
void	ft_img_p(struct s_window *m);
void	ft_img_e(struct s_window *m);
void	ft_struct_init(struct s_window *m);
int		map_create(struct s_window *m);
void	ft_check_zmienna(struct s_window *m);
void	ft_c(struct s_window *m, int v);
void	ft_w(struct s_window *m, int v);
void	ft_move(struct s_window *m, int v);
void	ft_e(struct s_window *m, int v);
void	ft_wsad(struct s_window *m, int v);
int		deal_key(int key, struct s_window *m);
int		close_window(struct s_window *m);
int		ft_check_de_map(struct s_window *m);
int		ft_get_ready(struct s_window *m, char *argc);
int		ft_landscape(struct s_window *m);

#endif
