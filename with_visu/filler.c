/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:43:38 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/05 13:43:40 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
#include "filler.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "./visual/minilibx/mlx.h"
# define COLOR_GRID 0x00555555
# define RED 0x00C00000
# define PINK 0x00FF8585
# define GREEN 0x0000C000
# define LIGHT_GR 0x0085FF85
# define INIT_SCALE 25
# define SCOREBOARD 100

void drow_cell(void *mlx_ptr, void *win_ptr, int i, int j, int cof, t_data *d, char c)
{
	int x;
	int y;
	int y_min;
	int x_min;

	//y = ((j + 1) * cof) + (d->m_h * cof)/ 15;
	y = (j  * cof) + (d->m_h * cof)/ 15;
	y_min = y;
	while(++y < (y_min + cof))
	{
		x = i * cof;
		x_min = x;
		while(++x < x_min + cof)
		{
			if (c =='O')
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, GREEN);
			else if (c == 'X')
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, RED);
			else if (c == 'o')
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, LIGHT_GR);
			else if (c == 'x')
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, PINK);
		}
	}
}

void all_ok(void *mlx_ptr, void *win_ptr, int cof, t_data *d)
{
	int i;
	int j;

	i = -1;
	while (d->m[++i])
	{
		j = -1;
		while (d->m[i][++j])
		{
			if (d->m[i][j] == 'O')
				drow_cell(mlx_ptr, win_ptr, j , i, cof, d, 'O');
			else if (d->m[i][j] == 'X')
				drow_cell(mlx_ptr, win_ptr, j , i, cof, d, 'X');
			else if (d->m[i][j] == 'o')
				drow_cell(mlx_ptr, win_ptr, j , i, cof, d, 'o');
			else if (d->m[i][j] == 'x')
				drow_cell(mlx_ptr, win_ptr, j , i, cof, d, 'x');
		}
	}
}

void visual_run(t_data *d_prev, t_coords *sh_prev,void **mlx_ptr, void **win_ptr)
{
	int i;
	int j;
	int cof;
	t_data		*d;
	t_coords	*sh_coords;
	i = 0;
	j = 0;
	
	d = d_prev;
	sh_coords = sh_prev;
	char *str;
	int k =5;
	cof = 50;
	if (d->m_h > 15 && d->m_w > 15)
		cof = 25;
	*mlx_ptr = mlx_init();
	*win_ptr = mlx_new_window(*mlx_ptr, (d->m_w *cof), (d->m_h *cof) + (d->m_h *cof)/ 15, "Filler");
	//vertical;
	while (j <= (d->m_w *cof))
	{
		i = (d->m_h *cof)/ 15;
		while (++i < (d->m_h *cof) + 80)
			mlx_pixel_put(*mlx_ptr, *win_ptr, j, i, COLOR_GRID);
		j += cof;
	}
	//horizontal
	i = (d->m_h *cof)/ 15;
	while (i <= (d->m_h *cof) + cof)
	{
		j = 0;
		while (++j < (d->m_w *cof))
			mlx_pixel_put(*mlx_ptr, *win_ptr, j, i, COLOR_GRID);
		i += cof;
	}
	//all_ok(mlx_ptr, win_ptr, cof, d);
	//mlx_loop(mlx_ptr);
}

void			map_free(char **m)
{
	int			i;

	i = -1;
	while (m && m[++i])
		free(m[i]);
	free(m[i]);
	free(m);
}

void			shape_free(char **sh)
{
	int			i;

	i = -1;
	while (sh && sh[++i])
		free(sh[i]);
	free(sh[i]);
	free(sh);
}

int				num_of_stars(t_data *d)
{
	int			stars;
	int			i;
	int			j;

	stars = 0;
	i = 0;
	while (d->sh && d->sh[i])
	{
		j = 0;
		while (d->sh[i][j])
		{
			if (d->sh[i][j] == '*')
				stars++;
			j++;
		}
		i++;
	}
	return (stars);
}

void			norm0(t_data *d, t_coords *sh_c)
{
	while (d->sh[sh_c->y] && d->sh[sh_c->y][sh_c->x] != '*')
	{
		sh_c->x++;
		if (d->sh[sh_c->y][sh_c->x] == '\0')
		{
			sh_c->y++;
			sh_c->x = 0;
		}
	}
}

int				norm1(t_data *d, t_coords *sh_c, int n_c, int n_r)
{
	char		en;

	if (d->s == 'O')
		en = 'X';
	else
		en = 'O';
	if ((d->l_c + d->sh_w) >= d->m_w
	|| (d->l_r + d->sh_h) >= d->m_h)
		return (0);
	if ((d->l_c + sh_c->x - n_c) >= 0 && (d->l_r + sh_c->y - n_r) >= 0
		&& (d->l_c + sh_c->x - n_c) <= (d->m_w - 1)
		&& (d->l_r + sh_c->y - n_r) <= (d->m_h - 1)
		&& (d->m[d->l_r + sh_c->y - n_r][d->l_c + sh_c->x - n_c] == d->s
		|| d->m[d->l_r + sh_c->y - n_r][d->l_c + sh_c->x - n_c] == '.'
		|| d->m[d->l_r + sh_c->y - n_r][d->l_c + sh_c->x - n_c] == d->s + 32)
		&& d->m[d->l_r + sh_c->y - n_r][d->l_c + sh_c->x - n_c] != en
		&& d->m[d->l_r + sh_c->y - n_r][d->l_c + sh_c->x - n_c] != en + 32)
		return (1);
	else
		return (0);
}

void			norm2(t_data *d, t_coords *sh_c, int n_c, int n_r)
{
	if ((d->m[d->l_r + sh_c->y - n_r][d->l_c + sh_c->x - n_c] == d->s
		|| d->m[d->l_r + sh_c->y - n_r][d->l_c + sh_c->x - n_c] == d->s + 32))
		d->num_of_sign++;
	if (d->sh[sh_c->y][sh_c->x + 1] == '\0' && !(sh_c->x = 0))
		sh_c->y++;
	else
		sh_c->x++;
}

int				norm3(t_data *d, int n_c, int n_r)
{
	if (d->l_c - n_c < 0 || d->l_r - n_r < 0
		|| d->num_of_sign != 1)
		return (0);
	d->l_c = d->l_c - n_c;
	d->l_r = d->l_r - n_r;
	return (1);
}

int				ft_is_possible(t_data *d, t_coords *sh_c, int n_c, int n_r)
{
	int			i;
	int			stars_num;

	i = -1;
	d->num_of_sign = 0;
	sh_c->y = 0;
	sh_c->x = 0;
	stars_num = num_of_stars(d);
	while (++i < stars_num)
	{
		norm0(d, sh_c);
		if (d->sh[sh_c->y][sh_c->x] == '*' && i == 0)
		{
			n_c = sh_c->x;
			n_r = sh_c->y;
		}
		if (norm1(d, sh_c, n_c, n_r))
			norm2(d, sh_c, n_c, n_r);
		else
			return (0);
	}
	if (norm3(d, n_c, n_r) == 0)
		return (0);
	return (1);
}

int				play0(t_data *d, t_coords *sh_coords)
{
	int			i;

	i = 0;
	d->l_c = d->m_w - 1;
	d->l_r = d->m_h - 1;
	while (i != 1)
	{
		if ((i = ft_is_possible(d, sh_coords, 0, 0)))
			ft_printf("%d %d\n", d->l_r, d->l_c);
		else
		{
			if ((d->l_r == 0 && d->l_c == 0))
			{
				ft_printf("%d %d\n", 0, 0);
				return (0);
			}
			else if (d->l_c == 0 && d->l_r > 0 && (d->l_c = d->m_w - 1))
				d->l_r--;
			else if (d->l_c != 0)
				d->l_c--;
		}
	}
	return (1);
}

int				play1(t_data *d, t_coords *sh_coords)
{
	int			i;

	i = 0;
	d->l_c = 0;
	d->l_r = 0;
	while (i != 1)
	{
		if ((i = ft_is_possible(d, sh_coords, 0, 0)))
			ft_printf("%d %d\n", d->l_r, d->l_c);
		else
		{
			if ((d->l_r == (d->m_h - 1) && d->l_c == (d->m_w - 1)))
			{
				ft_printf("%d %d\n", 0, 0);
				return (0);
			}
			if (d->l_c == (d->m_w - 1)
				&& d->l_r < (d->m_h - 1) && !(d->l_c = 0))
				d->l_r++;
			else if (d->l_c != (d->m_w - 1))
				d->l_c++;
		}
	}
	return (1);
}

void			algo_defind(t_data *d, t_coords sign_c)
{
	if (sign_c.x < (d->m_w / 2) && sign_c.y < (d->m_h / 2))
		d->way = right_down;
	else if (sign_c.x > (d->m_w / 2) && sign_c.y < (d->m_h / 2))
		d->way = left_down;
	else if (sign_c.x < (d->m_w / 2) && sign_c.y > (d->m_h / 2))
		d->way = right_up;
	else if (sign_c.x > (d->m_w / 2) && sign_c.y >= (d->m_h / 2))
		d->way = left_up;
	else
		d->way = right_down;
}

void			find_my_coords(t_data *d)
{
	t_coords	m;
	t_coords	sign_c;

	m.y = 0;
	while (m.y < d->m_h)
	{
		m.x = 0;
		while (m.x < d->m_w)
		{
			if (d->m[m.y][m.x] == d->s)
			{
				sign_c.x = m.x;
				sign_c.y = m.y;
			}
			m.x++;
		}
		m.y++;
	}
	algo_defind(d, sign_c);
}

void			shape_change(t_data *d, int fd)
{
	int			i;
	char		*str;

	i = 5;
	str = NULL;
	get_next_line(fd, &str);
	d->sh_h = ft_atoi(&str[i]);
	while (ft_isdigit(str[++i]))
		;
	d->sh_w = ft_atoi(&str[i]);
	free(str);
	i = -1;
	d->sh = (char**)malloc(sizeof(char*) * (d->sh_h + 1));
	if (d->sh == NULL)
	{
		ft_printf("0 0\n");
		exit(1);
	}
	while (++i < d->sh_h)
	{
		get_next_line(fd, &str);
		d->sh[i] = ft_strdup(str);
		free(str);
	}
	d->sh[i] = NULL;
}

void			player_num(int fd, t_data *d)
{
	char		*str;

	str = NULL;
	get_next_line(fd, &str);
	if (str && str[10] == '1')
		d->s = 'O';
	else if (str && str[10] == '2')
		d->s = 'X';
	free(str);
}

void			map_change_help(t_data *d)
{
	char		*str;
	int			i;
	int			fd;

	str = NULL;
	i = -1;
	fd = 0;
	get_next_line(fd, &str);
	free(str);
	while (++i < d->m_h)
	{
		get_next_line(fd, &str);
		d->m[i] = ft_strsub(str, 4, d->m_w);
		if (d->m[i] == NULL)
		{
			ft_printf("0 0\n");
			exit(1);
		}
		free(str);
	}
	d->m[i] = NULL;
}

void			map_change(t_data *d, int fd)
{
	char		*str;
	int			i;

	str = NULL;
	i = 7;
	get_next_line(fd, &str);
	d->m_h = ft_atoi(&str[i]);
	while (ft_isdigit(str[++i]))
		;
	d->m_w = ft_atoi(&str[i]);
	free(str);
	i = -1;
	d->m = (char**)malloc(sizeof(char*) * (d->m_h + 1));
	if (d->m == NULL)
	{
		ft_printf("0 0\n");
		exit(1);
	}
	map_change_help(d);
}

void			algo0(t_data *d, t_coords *sh_coords, int fd, void *mlx_ptr, void *win_ptr)
{
	while (play0(d, sh_coords))
	{
		all_ok(mlx_ptr, win_ptr, 50, d);
		// /sleep(1);
		map_free(d->m);
		shape_free(d->sh);
		map_change(d, fd);
		shape_change(d, fd);
	}
}

void			algo1(t_data *d, t_coords *sh_coords, int fd, void *mlx_ptr, void *win_ptr)
{
	while (play1(d, sh_coords))
	{
		all_ok(mlx_ptr, win_ptr, 50, d);
		//sleep(1);
		map_free(d->m);
		shape_free(d->sh);
		map_change(d, fd);
		shape_change(d, fd);
	}
}

int				main(void)
{
	t_data		*d;
	t_coords	*sh_coords;
	void *mlx_ptr;
	void *win_ptr;

	d = (t_data*)malloc(sizeof(t_data));
	sh_coords = (t_coords*)malloc(sizeof(t_coords));
	player_num(0, d);
	map_change(d, 0);
	shape_change(d, 0);
	visual_run(d, sh_coords, &mlx_ptr, &win_ptr);
	find_my_coords(d);
	if (d->way == 1 || d->way == 0)
		algo0(d, sh_coords, 0, mlx_ptr, win_ptr);
	else
		algo1(d, sh_coords, 0, mlx_ptr, win_ptr);
	//mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_loop(mlx_ptr);
	map_free(d->m);
	shape_free(d->sh);
	free(d);
	free(sh_coords);
	return (0);
}
