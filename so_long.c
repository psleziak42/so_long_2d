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
	int		s_w_x;	// window size
	int		s_w_y;
	int		w_x;	// window size helper
	int		w_y;
	int		i_h;
	int		i_w;
	int		h_i; // helpers;
	int		h_j;
	int		h_l;
	int		h_k;
	int		h_u;
	int		h_t;
	int		x; // wsad x
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

void	ft_img_c(struct s_window *m)
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

void	ft_img_w(struct s_window *m)
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


void	ft_img_p(struct s_window *m)
{
	if (m->zmienna1 == 1)
		m->filename = "img/ghost.xpm";
	else if (m->zmienna1 == 2)
		m->filename = "img/charmander.xpm";
	else
		m->filename = "img/krzew.xpm";
}

void	ft_img_e(struct s_window *m)
{
		if (m->zmienna1 != 2)
			m->filename = "img/wood.xpm";
		else
			m->filename = "img/grass.xpm";
}



int 	map_create(struct s_window *m)
{
	int x;

	x = 0;
	m->w_x = 0;
	m->w_y = 0;
	m->h_j = -1; // ta zmienna mogla by zostac uzyta w mapie checker zamiast x
	printf("%s\n", m->map);
	// zmienna -> to tak naprawde jest niepotrzebne, string ne musi sie wyswietlac, jest duszek!
	if (m->zmienna1 == 2) 	
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
	//
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
		else if (m->map[m->h_j] == '0')
			m->filename = "img/grass.xpm";
		else if (m->map[m->h_j] == 'C')
			ft_img_c(m);
		else if (m->map[m->h_j] == 'P')
			ft_img_p(m);
		else if (m->map[m->h_j] == 'E')
			ft_img_e(m);
		else if (m->map[m->h_j] == 'W')
			ft_img_w(m);
		m->img_instance = mlx_xpm_file_to_image(m->mlx_ptr, m->filename, &m->i_h, &m->i_w); // tu mogla by byc jakas funcka dla tych 2;
		mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->img_instance, m->w_x, m->w_y);
		m->w_x = m->w_x + m->i_w;
	}
	////------//////
	if (m->zmienna1 == 1) // to mozna pewnie zmienc jak bedzie wszedzie return 0 to = lost, return 1 = win; to tez nie jest potrzebne
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


//
//
// KEY FUNCTIONS //
//
//
void	ft_c(struct s_window *m, int v) // dla a, v = x - 1
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
	m->map[m->x + m->h_u] = 'P';	
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


//
//
// KEY FUNCTIONS //
// 
//


int		deal_key(int key, struct s_window *m) // 4 linijki za duzo
{
	int	v;

	v = 0; // dziala bez!
	if(key == ESC)
	{
		//free(m->map);
		//free(m->line);
		mlx_destroy_window(m->mlx_ptr, m->win_ptr);
		exit(1);
	}
	if (m->map_counter < 26)
		m->map_counter++;
	else
		return 0;
	//if (m->zmienna1)
	//	return 0;
	while (m->map[m->x] != 'P') 
		m->x++;
	if (key == s)
		v = m->x + m->h_u;
	else if (key == w)
		v = m->x - m->h_u;
	else if (key == a)
		v = m->x - 1;
	else if (key == d)
		v = m->x + 1;
	ft_wsad(m, v);
	/*if (m->map_counter < 26)
		m->map_counter++;
	else
		m->zmienna1 = 1;*/ // tu moze byc return 0 zeby skonczyc
	map_create(m);
	return 1; // return 0?
}

int	close_window(struct s_window *m)
{
	mlx_destroy_window(m->mlx_ptr, m->win_ptr);
	exit(1);
}
			
int	ft_check_de_map(struct s_window *m) // jedna linijka za duzo, sprawdz czy nie pomylilem zmiennych. Zamiast x mozna dac strukture.
{
	int x;

	x = 0;
	m->ECP = 0b00;	 // m->h_u = x;  m->h_t = y; m->h_i = calosc
	while (m->map[++x] != '\0')
	{
		if (m->map[x] == '\n' && m->map[x - 1] != '1' && m->map[x + 1] != '1')
			return 0;
		if (m->map[x] == 'E')
			m->ECP = m->ECP | E;
		if (m->map[x] == 'C')
			m->ECP = m->ECP | C;
		if (m->map[x] == 'P')
			m->ECP = m->ECP | P;
		if (m->map[x] != 'E' || m->map[x] != 'C' || m->map[x] != 'P' || m->map[x] != '0' || m->map[x] != '1' || m->map[x] != 'W')
			m->ECP = m->ECP | D;
	}
	if (((m->ECP | -128) != -128) || (m->h_u*m->h_t == m->h_i) || (m->h_u != m->h_t))
		return 0;
	x = x - 2;
	while (m->map[x] != '\n')
	{
		if (m->map[x--] != '1')
			return 0;
	}
	return 1;
}

int	ft_get_ready(struct s_window *m, char *argc)
{
	int i;

	i = 0;
	m->fd = open(argc, O_RDONLY);
	m->h_i = get_next_line(m->fd, &m->line);
	m->map = malloc(m->h_i * sizeof(char));
	if (!m->map)
		return 0;
	m->map = m->line;
	m->h_t = 0;
	while (m->map[++i] != '\0')
	{
		if(m->map[i] == '\n')
			m->h_t++; // sprawdzic czy nie dziele prezz 0, ale to powinno byc zweryfikowane w check de map);
	}	
	m->h_u = (m->h_i/m->h_t);
	m->s_w_x = (m->h_u - 1) * 32;
	m->s_w_y = m->h_t * 32;
	return 1;
}

int	ft_landscape(struct s_window *m)
{
	m->filename = "img/grass.xpm";
	m->img_instance = mlx_xpm_file_to_image(m->mlx_ptr, m->filename, &m->i_h, &m->i_w);
	m->w_x = 0;
	m->w_y = 0;
	while (m->w_y <= m->s_w_y)
	{
		while(m->w_x <= m->s_w_x)
		{
			mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->img_instance, m->w_x, m->w_y);
			m->w_x = m->w_x + m->i_w;
		}
		m->w_y = m->w_y + m->i_h;
		m->w_x = 0;
	}
	printf("%s\n", m->map);
	m->w_x = 0;
	m->w_y = 0;
	return 1;
}


int main(int argv, char **argc)
{
	struct s_window	m;

	if (!ft_get_ready(&m, argc[1]))
		perror("Error");
	if (!ft_check_de_map(&m))
		perror("Error");
	//window inicialize //
	m.mlx_ptr = mlx_init();
	m.win_ptr = mlx_new_window(m.mlx_ptr, m.s_w_x, m.s_w_y, "PoK3M0Ny");
	mlx_key_hook(m.win_ptr, deal_key, &m); // it returns inteager :) can be used for 0 and 1; // if -> return 0
	mlx_hook(m.win_ptr, 17, 1L << 0, close_window, &m);
	if (!ft_landscape(&m))
		perror("Error");
	// zmienna1 check; ??
	if (!map_create(&m)) // co to jest?
		perror("Error");
	//ft_putnbr_fd(m.map_counter, 1);
	//mlx_string_put(m.mlx_ptr, m.win_ptr, m.s_w_x - 55, 32, m.color, ft_itoa(m.map_counter));
	mlx_loop(m.mlx_ptr);
}
