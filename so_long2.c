#include "mlx.h"
#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

#define ESC 53
#define	X	17
#define f 	3
#define	a	0
#define s	1
#define	w	13
#define d	2
#define E	10000000
#define C	01000000
#define P	00100000
#define D 	00000001

struct s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_instance;
	void	*img_night;
	char	*adres;
	char	*filename;
	char	*line;
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
	//int		fire_loop;
	char	ECP;
};

/*void	initializer(struct s_window *m)
{
	m->fire_loop = 0;
}*/





int		get_next_line(int fd, char **line)
{
	char	buf;
	int		i;

	(*line) = malloc(8192);
	if (!*line)
		return -1;
	if (fd < 0 || !(*line))
	{
		free(*line);
		return 0;
	}
	i = 0;
	while(read(fd, &buf, 1)) 		
		(*line)[i++] = buf;
	(*line)[i] = '\0';
	i = 0;
	return ft_strlen(*line);
}






int 	map_create(struct s_window *m)
{
	int x;

	x = 0;
	m->w_x = 0;
	m->w_y = 0;
	m->h_j = -1;
	printf("%s\n", m->map);
	if (m->zmienna1 == 2) // tu jest zle: trzeba ustawic ze you win pojawia sie tylko wtedy gdy najedziemy na finish a nie gdy na ogien ale mamy 2 coiny.
	{
		x = 0;
		while (m->map[x] != 'C' && m->map[x])
			x++;
		if (x == m->h_i)
			m->zmienna1 = 2;
		else
			m->zmienna1 = 1;
	}
	else if(m->zmienna1 == 1)
		m->zmienna1 = 1;
	while (m->map[++m->h_j] != '\0')
	{
		if (m->map[m->h_j] == '\n')
		{
			m->w_x = 0;
			m->w_y = m->w_y + m->i_h;
			continue;
		}
		if (m->map[m->h_j] == '1')
			m->filename = "img/rock.xpm";
		else if (m->map[m->h_j] == 'C')
		{
			m->filename = "img/grass.xpm";
			m->img_instance = mlx_xpm_file_to_image(m->mlx_ptr, m->filename, &m->i_h, &m->i_w);
			mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->img_instance, m->w_x, m->w_y);
			if (m->map_counter % 4 == 0)
				m->filename = "img/coin-4.xpm";
			else if (m->map_counter % 3 == 0)
				m->filename = "img/coin-3.xpm";
			else if (m->map_counter % 2 == 0)
				m->filename = "img/coin-2.xpm";
			else
				m->filename = "img/coin-1.xpm";
		}
		else if (m->map[m->h_j] == 'P')
		{
			if (m->zmienna1 == 1)
				m->filename = "img/ghost.xpm";
			else if (m->zmienna1 == 2)
				m->filename = "img/charmander.xpm";
			else
				m->filename = "img/krzew.xpm";
		}
		else if (m->map[m->h_j] == 'E')
		{
			if (m->zmienna1 != 2)
				m->filename = "img/wood.xpm";
			else
				m->filename = "img/grass.xpm";
		}
		else if (m->map[m->h_j] == 'W')
		{
			m->filename = "img/grass.xpm";
			m->img_instance = mlx_xpm_file_to_image(m->mlx_ptr, m->filename, &m->i_h, &m->i_w);
			mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->img_instance, m->w_x, m->w_y);
			if (m->map_counter % 4 == 0)
				m->filename = "img/4.xpm";
			else if (m->map_counter % 3 == 0)
				m->filename = "img/3.xpm";
			else if (m->map_counter % 2 == 0)
				m->filename = "img/2.xpm";
			else
				m->filename = "img/1.xpm";
		}
		else if (m->map[m->h_j] == '0')
			m->filename = "img/grass.xpm";
		m->img_instance = mlx_xpm_file_to_image(m->mlx_ptr, m->filename, &m->i_h, &m->i_w);
		mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->img_instance, m->w_x, m->w_y);
		m->w_x = m->w_x + m->i_w;
	}
	if (m->zmienna1 == 1)
			mlx_string_put(m->mlx_ptr, m->win_ptr, m->s_w_x/2, m->s_w_y/2, 0x00FF0000, "YOU LOST");
	else if (m->zmienna1 == 2)
			mlx_string_put(m->mlx_ptr, m->win_ptr, m->s_w_x/2, m->s_w_y/2, 0x0000FF00, "YOU WON");
	// display no of movements in shell //
	ft_putnbr_fd(m->map_counter, 1);
	write(1, "\n", 1);
	mlx_string_put(m->mlx_ptr, m->win_ptr, m->s_w_x - 55, 32, m->color, ft_itoa(m->map_counter));




	return 1;
}






int	color(int c_t, int c_r, int c_g, int c_b, struct s_window *m)
{
	return(m->c_t << 24 | m->c_r << 16 | m->c_g << 8 | m->c_b);
}


int		deal_key(int key, struct s_window *m)
{
	static int	x;
	char	temp;
	
	if(key == ESC)
	{
		//free(m->map);
		//free(m->line);
		mlx_destroy_window(m->mlx_ptr, m->win_ptr);
		exit(1);

	}
	if (m->zmienna1)
		return 0;
	while (m->map[x] != 'P')
		x++;
	if (m->h_t == 1)
	{
		mlx_string_put(m->mlx_ptr, m->win_ptr, m->s_w_x/2, m->s_w_y/2, 0x00FFE0FF, "lost");
		return 0;
	}
	if (key == s) // jak pod C jest kamien to wyrzuca mnie po za mape
	{
		if (m->map[x+m->h_u] != '1')
		{
			if (m->map[x+m->h_u] == 'C')
			{
				temp = m->map[x];
				m->map[x] = '0';
				m->map[x + m->h_u] = temp;
				x = m->h_u + x;
			}
			else if (m->map[x+m->h_u] == 'W')
			{
				m->zmienna1 = 1;
				//temp = m->map[x];
				m->map[x] = '0';
				m->map[x + m->h_u] = 'P';
			}
			else if (m->map[x+m->h_u] == 'E')
			{
				m->zmienna1 = 2;
				//temp = m->map[x];
				m->map[x] = '0';
				m->map[x + m->h_u] = 'P';
			}
			else
			{
				temp = m->map[x];
				m->map[x] = m->map[x + m->h_u];
				m->map[x + m->h_u] = temp;
				x = m->h_u + x;
			}
		}
	}
	else if (key == w)
	{
		if (m->map[x-m->h_u] != '1')
		{
			if (m->map[x-m->h_u] == 'C')
			{
				temp = m->map[x];
				m->map[x] = '0';
				m->map[x - m->h_u] = 'P';
				x = m->h_u - x;
			}
			else if (m->map[x - m->h_u] == 'W')
			{
				m->zmienna1 = 1;
				temp = m->map[x];
				m->map[x] = '0';
				m->map[x - m->h_u] = 'P';
			}
			else
			{
				temp = m->map[x];
				m->map[x] = m->map[x - m->h_u];
				m->map[x - m->h_u] = temp;
				x = x - m->h_u;
			}
		}
	}
	else if (key == d)
	{
		if (m->map[x+1] != '1')
		{
			if (m->map[x+1] == 'C')
			{
				temp = m->map[x];
				m->map[x] = '0';
				m->map[x + 1] = 'P';
				x++;
			}
			else if (m->map[x+1] == 'W')
			{
				m->zmienna1 = 1;
				temp = m->map[x];
				m->map[x] = '0';
				m->map[x + 1] = 'P';
			}
			else
			{
				temp = m->map[x];
				m->map[x] = m->map[x + 1];
				m->map[x + 1] = temp;
				x++;
			}
		}
	}
	else if (key == a)
	{
		if (m->map[x-1] != '1')
		{
			if (m->map[x - 1] == 'C')
			{
				temp = m->map[x];
				m->map[x] = '0';
				m->map[x -1] = 'P';
				x--;
			}
			else if (m->map[x - 1] == 'W')
			{
				m->zmienna1 = 1;
				temp = m->map[x];
				m->map[x] = '0';
				m->map[x - 1] = 'P';
			}
			else
			{
				temp = m->map[x];
				m->map[x] = m->map[x -1];
				m->map[x - 1] = temp;
				x--;
			}
		}
	}
	if (m->map_counter < 26)
		m->map_counter++;
	else
		m->zmienna1 = 1;
	//printf("moves %d\n", m->map_counter);
	map_create(m);
	return 0;
}

int	close_window(struct s_window *m)
{
	mlx_destroy_window(m->mlx_ptr, m->win_ptr); // poblem seg fault..
	exit(1);
}
			
int	ft_check_de_map(struct s_window *m)
{
	int x;  
	int e; 	
	int y; 	
	int o;
	m->ECP = 0b00;
	x = -1;
	e = 0;
	while (m->map[++x] != '\n')
	{
		if (m->map[x] != '1')
			return 0;
		e++;
	}
	x = e;
	y = 1;
	while (m->map[++x] != '\0')
	{
		if (m->map[x] == '\n' && m->map[x - 1] != '1' && m->map[x + 1] != '1')
			return 0;
		if (m->map[x] == '\n')	
			y++;
		if (m->map[x] == 'E')
			m->ECP = m->ECP | E;
		if (m->map[x] == 'C')
			m->ECP = m->ECP | C;
		if (m->map[x] == 'P')
			m->ECP = m->ECP | P;
		if (m->map[x] != 'E' && m->map[x] != 'C' && m->map[x] != 'P' && m->map[x] != '0' && m->map[x] != '1')
			m->ECP = m->ECP | D;
	}
	if ((m->ECP & -128) != -128)
	{
		perror("Error");
		return 0;
	}
	printf("e*y = %d\n", e*y);
	printf("y = %d\n", y);
	printf("x = %d\n", x);
	if ((e+1)*y != x) 
		return 0;
	if (e == y)
		return 0;
	x = x - 2;
	printf("%c\n", m->map[x]);
	while (m->map[x] != '\n')
	{
		printf("m->mapx%c\n", m->map[x]);
		if (m->map[x] != '1')
			return 0;
		x--;
	}
	return 1;
}

int	ft_get_ready(struct s_window *m, char *argc)
{
	int i;

	i = 0;
	m->fd = open(argc, O_RDONLY);
	m->h_i = get_next_line(m->fd, &m->line);
	m->map = malloc(m->h_i * sizeof(char)); // tu moze byc blad!!
	m->map = m->line;
	m->h_t = 0;
	while (m->map[++i] != '\0')
	{
		if(m->map[i] == '\n')
			m->h_t++;
	}	
	m->h_u = (m->h_i/m->h_t);
	m->s_w_x = (m->h_u - 1) * 32;
	m->s_w_y = m->h_t * 32;
	return 1;
}

int main(int argv, char **argc)
{
	struct s_window	m;

	if (!ft_get_ready(&m, argc[1]));
		perror("Error");
	/*int	k;
	int	j;
	struct s_window	m;

	k = -1;
	j = 0;
	// preparing to start mlx // 
	m.fd = open(argc[1], O_RDONLY);
	m.h_i = get_next_line(m.fd, &m.line);
	m.map = malloc(m.h_i * sizeof(char)); // tu moze byc blad!!
	m.map = m.line;
	m.h_t = 0;
	while (m.map[++k] != '\0')
	{
		if(m.map[k] == '\n')
			m.h_t++;
	}	
	m.h_u = (m.h_i/m.h_t);
	m.s_w_x = (m.h_u - 1) * 32;
	m.s_w_y = m.h_t * 32;*/
	if (ft_check_de_map(&m) == 0)
		return 0;
	//window inicialize //
	m.mlx_ptr = mlx_init();
	m.win_ptr = mlx_new_window(m.mlx_ptr, m.s_w_x, m.s_w_y, "PoK3M0Ny");
	mlx_key_hook(m.win_ptr, deal_key, &m);
	mlx_hook(m.win_ptr, 17, 1L << 0, close_window, &m);
	// filling map with grass
	m.filename = "img/grass.xpm";
	m.img_instance = mlx_xpm_file_to_image(m.mlx_ptr, m.filename, &m.i_h, &m.i_w);
	m.w_x = 0;
	m.w_y = 0;
	while (m.w_y <= m.s_w_y)
	{
		while(m.w_x <= m.s_w_x)
		{
			mlx_put_image_to_window(m.mlx_ptr, m.win_ptr, m.img_instance, m.w_x, m.w_y);
			m.w_x = m.w_x + m.i_w;
		}
		m.w_y = m.w_y + m.i_h;
		m.w_x = 0;
	}
	printf("%s\n", m.map);
	m.w_x = 0;
	m.w_y = 0;
	//j = -1;
	if (!map_create(&m)) // co to jest?
		return 0;
	mlx_loop(m.mlx_ptr);
}
