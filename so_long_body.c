#include "so_long.h"

int	map_create(struct s_window *m)
{
	ft_struct_init(m);
	while (m->map[++m->h_j] != '\0')
	{
		if (m->map[m->h_j] == '\n')
		{
			m->w_x = 0;
			m->w_y = m->w_y + m->i_h;
			continue ;
		}
		if (m->map[m->h_j] == '1')
			m->f = "img/rock.xpm";
		else if (m->map[m->h_j] == '0')
			m->f = "img/grass.xpm";
		else if (m->map[m->h_j] == 'C')
			ft_img_c(m);
		else if (m->map[m->h_j] == 'P')
			ft_img_p(m);
		else if (m->map[m->h_j] == 'E')
			ft_img_e(m);
		else if (m->map[m->h_j] == 'W')
			ft_img_w(m);
		ft_image(m);
		m->w_x = m->w_x + m->i_w;
	}
	return (1);
}

int	ft_landscape(struct s_window *m)
{
	m->f = "img/grass.xpm";
	m->i_i = mlx_xpm_file_to_image(m->mlx_p, m->f, &m->i_h, &m->i_w);
	m->w_x = 0;
	m->w_y = 0;
	while (m->w_y <= m->s_w_y)
	{
		while (m->w_x <= m->s_w_x)
		{
			mlx_put_image_to_window(m->mlx_p, m->w_p, m->i_i, m->w_x, m->w_y);
			m->w_x = m->w_x + m->i_w;
		}
		m->w_y = m->w_y + m->i_h;
		m->w_x = 0;
	}
	m->w_x = 0;
	m->w_y = 0;
	return (1);
}

int	ft_check_de_map(struct s_window *m)
{
	ft_struct_init(m);
	while (m->map[++m->h_j] != '\0')
	{
		if (m->map[m->h_j] == '\n' && m->map[m->h_j - 1] != '1'
			&& m->map[m->h_j + 1] != '1')
			return (0);
		else if (m->map[m->h_j] == 'E')
			m->ECP = m->ECP | E;
		else if (m->map[m->h_j] == 'C')
			m->ECP = m->ECP | C;
		else if (m->map[m->h_j] == 'P')
			m->ECP = m->ECP | P;
		else if ((m->map[m->h_j] != '0') && (m->map[m->h_j] != '1')
			&& (m->map[m->h_j] != 'W') && (m->map[m->h_j] != '\n'))
			m->ECP = m->ECP | V;
	}
	if (m->ECP != 112)
		return (0);
	m->h_j = m->h_j - 2;
	while (m->map[--m->h_j] != '\n')
	{
		if (m->map[m->h_j] != '1')
			return (0);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char	buf;
	int		i;

	(*line) = malloc(8192);
	if (!*line)
		return (0);
	if (fd < 0 || !(*line))
	{
		free(*line);
		return (0);
	}
	i = 0;
	while (read(fd, &buf, 1))
		(*line)[i++] = buf;
	(*line)[i] = '\0';
	i = 0;
	return (ft_strlen(*line));
}

int	ft_get_ready(struct s_window *m, char *argc)
{
	m->h_j = -1;
	m->fd = open(argc, O_RDONLY);
	m->h_i = get_next_line(m->fd, &m->line);
	m->map = malloc(m->h_i * sizeof(char));
	if (!m->map)
		return (0);
	m->map = m->line;
	m->h_t = 0;
	while (m->map[++m->h_j] != '\0')
	{
		if (m->map[m->h_j] == '\n')
			m->h_t++;
	}	
	m->h_u = (m->h_i / m->h_t);
	printf("m->h_u %d\n, m->h_i %d\n, m->h_t %d\n", m->h_u, m->h_i, m->h_t);
	if (m->h_t < 2 || (m->h_t == m->h_u - 1) || (m->h_u * m->h_t != m->h_i))
		return (0);
	m->s_w_x = (m->h_u - 1) * 32;
	m->s_w_y = m->h_t * 32;
	return (1);
}
