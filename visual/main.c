/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:10:48 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/15 16:10:51 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"
#include <stdlib.h>
//#include "visual.h"
#include <stdio.h>
#include "libft/libft.h"
#include "../filler.h"
# define COLOR_GRID 0x00555555
# define RED 0x00C00000
# define PINK 0x00FF8585
# define GREEN 0x0000C000
# define LIGHT_GR 0x0085FF85
# define INIT_SCALE 25
# define SCOREBOARD 100

int glob = 0;

typedef struct s_pp
{
	t_data *d;
	void *mlx_ptr;
	void *win_ptr;
	char *player1;
	char *player2;
}				t_p;

static int	win_keys(int keycode)
{
	if (keycode == 53)
	{
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 49)
		sleep(5);
	return (0);
}

void			map_free(char **m)
{
	int			i;

	i = -1;
	if (!m || !*m)
		return;
	while (m && m[++i])
		free(m[i]);
	free(m[i]);
	free(m);
}

void			shape_free(char **sh)
{
	int			i;

	i = -1;
	if (!sh || !*sh)
		return;
	while (sh && sh[++i])
		free(sh[i]);
	free(sh[i]);
	free(sh);
}


void drow_cell(void **mlx_ptr, void **win_ptr, int i, int j, int cof, t_data *d, char c)
{
	int x;
	int y;
	int y_min;
	int x_min;

	y = (j  * cof) + (d->m_h * cof)/ 15;
	y_min = y;
	while(++y < (y_min + cof))
	{
		x = i * cof;
		x_min = x;
		while(++x < x_min + cof)
		{
			if (c =='O')
				mlx_pixel_put(*mlx_ptr, *win_ptr, x, y, GREEN);
			else if (c == 'X')
				mlx_pixel_put(*mlx_ptr, *win_ptr, x, y, RED);
			else if (c == 'o')
				mlx_pixel_put(*mlx_ptr, *win_ptr, x, y, LIGHT_GR);
			else if (c == 'x')
				mlx_pixel_put(*mlx_ptr, *win_ptr, x, y, PINK);
		}
	}
}

void all_ok(t_p *p ,int cof)
{
	int i;
	int j;

	i = -1;
	while (p->d->m[++i])
	{
		j = -1;
		while (p->d->m[i][++j])
		{
			if (p->d->m[i][j] == 'O')
				drow_cell(&p->mlx_ptr, &p->win_ptr, j , i, cof, p->d, 'O');
			else if (p->d->m[i][j] == 'X')
				drow_cell(&p->mlx_ptr, &p->win_ptr, j , i, cof, p->d, 'X');
			else if (p->d->m[i][j] == 'o')
				drow_cell(&p->mlx_ptr, &p->win_ptr, j , i, cof, p->d, 'o');
			else if (p->d->m[i][j] == 'x')
				drow_cell(&p->mlx_ptr, &p->win_ptr, j , i, cof, p->d, 'x');
		}
	}
}

void visual_run(t_data *d, t_coords *sh_coords,void **mlx_ptr, void **win_ptr)
{
	int i;
	int j;
	int cof;
	i = 0;
	j = 0;
	
	char *str;
	int k =5;
	cof = 50;
	if (d->m_h > 15 && d->m_w > 15)
		cof = 25;
	if (d->m_h > 50)
		cof = 10;
	*mlx_ptr = mlx_init();
	*win_ptr = mlx_new_window(*mlx_ptr, (d->m_w *cof), (d->m_h *cof) + (d->m_h *cof)/ 15, "Filler");
	mlx_string_put(*mlx_ptr, *win_ptr,(d->m_w *cof)*4/10, (d->m_h * cof)/ 15 * 3/10, GREEN , "Have a good fight!");
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
	while (i <= (d->m_h *cof) + (d->m_h *cof)/ 15)
	{
		j = 0;
		while (++j < (d->m_w *cof))
			mlx_pixel_put(*mlx_ptr, *win_ptr, j, i, COLOR_GRID);
		i += cof;
	}
}

void final(t_data *d, t_p *p, char *str)
{
	printf("%s\n", str);
	get_next_line(0, &str);
	printf("%s\n", str);
	mlx_string_put(p->mlx_ptr, p->win_ptr,(d->m_w * 50) *3/10, (d->m_h * 50)/ 300, GREEN , "num1/");
	mlx_string_put(p->mlx_ptr, p->win_ptr,(d->m_w * 50) *6/ 10, (d->m_h * 50)/ 300, RED , "num2");
	sleep(5);
	//exit(1);
}

int			shape_change(t_data *d, int fd, int sinko, t_p *p)
{
	int			i;
	char		*str;
	int 		k;
	int num1;
	int num2;

	i = 5;
	k = -1;
	str = NULL;
	str = ft_strdup("a");
	get_next_line(fd, &str);
	if (ft_strncmp(str, "== ", 2) == 0)
	{	
		printf("%s\n", str);
		num1 = ft_atoi(&str[10]);
		get_next_line(0, &str);
		num2 = ft_atoi(&str[10]);
		printf("%s\n", str);
		p->mlx_ptr = mlx_init();
		p->win_ptr = mlx_new_window(p->mlx_ptr, 400, 400, "Winner");
	
		if (num1 > num2)
			mlx_string_put(p->mlx_ptr, p->win_ptr,150, 150, GREEN , ft_strjoin(p->player1, " won!!!"));
		else if (num1 < num2)
			mlx_string_put(p->mlx_ptr, p->win_ptr,150, 150, GREEN , ft_strjoin(p->player2, " won!!!"));
		else
			mlx_string_put(p->mlx_ptr, p->win_ptr,150, 150, PINK , "Drawn");
		mlx_loop(p->mlx_ptr);
		exit(1);
	}
	while (ft_strncmp(str, "Piece", 4))
		get_next_line(fd, &str);
	d->sh_h = ft_atoi(&str[i]);
	while (ft_isdigit(str[++i]))
		;
	d->sh_w = ft_atoi(&str[i]);
	free(str);
	i = -1;
	d->sh = (char**)malloc(sizeof(char*) * (d->sh_h + 1));
	if (d->sh == NULL)
		return (0);
	while (++i < d->sh_h)
	{
		get_next_line(fd, &str);
		d->sh[i] = ft_strdup(str);
		if (d->sh[i] == NULL)
			return (0);
		free(str);
	}
	d->sh[i] = NULL;
	i = -1;
	while(d->sh[++i])
		printf("A%s\n", d->sh[i]);
	get_next_line(fd, &str);
	printf("-A%s\n", str);
	if ((!ft_strncmp(str, "<got (O): [0, 0]", 16) || !ft_strncmp(str, "<got (X): [0, 0]", 16)))
	{	
		glob = 3;
		shape_change(p->d, 0, 4, p);
		all_ok(p ,10);
		return (0);
	}
	if (str)
		free(str);
	return (0);
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
		return ;
		free(str);
	}
	d->m[i] = NULL;
	i = -1;
}

int			map_change(t_data *d, int fd, int res)
{
	char		*str;
	int			i;
	int k;

	str = NULL;
	str = ft_strdup("a");
	k = -1;
	i = 7;
	while (ft_strncmp(str, "Plateau", 5))
		get_next_line(fd, &str);
	printf("B%s\n", str);
	d->m_h = ft_atoi(&str[i]);
	while (ft_isdigit(str[++i]))
		;
	d->m_w = ft_atoi(&str[i]);
	free(str);
	i = -1;
	d->m = (char**)malloc(sizeof(char*) * (d->m_h + 1));
	if (d->m == NULL)
		return (0);
	map_change_help(d);
	printf("C\n");
	while(d->m[++i])
		printf("D%s\n", d->m[i]);
	return (1);
}

char *setplayer(char *str)
{
	int i;
	int j;
	int i_need;
	char *res;
	int k;

	j = 0;
	i = -1;
	k = 0;
	while(str[++i] && ft_strncmp(&str[i], ".filler", 5))
		;
	j = i - 1;
	while(str[j]!= '/')
		j--;
	j++;
	i_need = i - j;
	res = (char*)malloc(sizeof(char) * (i_need + 1));
	while (j < i)
	{
		res[k] = str[j];
		j++;
		k++;
	}
	res[k] = '\0';
	return (res);
}

int  parser(void *param)
{	
	int res = 0;
	char *str;

	t_p *p;
	str = NULL;
	p = (t_p *)param;
	if (glob !=1 && glob != 3)
	{
		map_change(p->d, 0, res);
		res = 0;
		res = shape_change(p->d, 0, 4, p);
		all_ok(p ,10);
		map_free(p->d->m);
		shape_free(p->d->sh);
	}
/*	if (glob == 1)
	{
		shape_change(p->d, 0, 4, p);
		all_ok(p ,50);
		glob = 3;
	}*/
	if (glob == 3)
		{
			map_change(p->d, 0, res);
			res = 0;
			res = shape_change(p->d, 0, 4, p);
			all_ok(p ,10);
			map_free(p->d->m);
			shape_free(p->d->sh);
		}
	return (0);
}

int main(void)
{
	void *mlx_ptr;
	void *win_ptr;
	t_p *p;
	int i;
	int j;
	int cof;
	t_data		*d;
	t_coords	*sh_coords;
	i = 0;
	j = 0;
	int res;
	p = (t_p*)malloc(sizeof(t_p));
	d = (t_data*)malloc(sizeof(t_data));
	sh_coords = (t_coords*)malloc(sizeof(t_coords));
	char *str;
	char *player1;
	char *player2;
	int k =10;
	str = NULL;
	res = 0;
	while (--k)
	{
		get_next_line(0, &str);
		if (!ft_strncmp(str, "$$$ exec p1 :", 13))
			p->player1 = setplayer(str);
		if (!ft_strncmp(str, "$$$ exec p2 :", 13))
			p->player2 = setplayer(str);
		free(str);
	}
	map_change(d, 0, 0);
	p->d = NULL;
	p->mlx_ptr = NULL;
	p->win_ptr = NULL;
	res = shape_change(d, 0, 4, p);
	visual_run(d, sh_coords, &mlx_ptr, &win_ptr);
	p->d = d;
	p->mlx_ptr = mlx_ptr;
	p->win_ptr = win_ptr;
	all_ok(p, 10);
	mlx_loop_hook(mlx_ptr, parser, (void*)p);
	mlx_loop(mlx_ptr);
	return (0);
}
