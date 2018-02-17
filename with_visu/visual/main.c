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

/*
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
			printf("0 0\n");
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
		printf("0 0\n");
		exit(1);
	}
	map_change_help(d);
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
		printf("0 0\n");
		exit(1);
	}
	while (++i < d->sh_h)
	{
		get_next_line(fd, &str);
		d->sh[i] = ft_strdup(str);
		free(str);
	}
	d->sh[i] = NULL;
}*/
int main(void)
{
	void *mlx_ptr;
	void *win_ptr;

	int i;
	int j;
	int cof;
	t_data		*d;
	t_coords	*sh_coords;
	i = 0;
	j = 0;
	d = (t_data*)malloc(sizeof(t_data));
	sh_coords = (t_coords*)malloc(sizeof(t_coords));
	char *str;
	int k =5;
	while (!ft_strstr(str, "launched"))
	{
		get_next_line(0, &str);
		//printf("%s\n", str);

	}
	map_change(d, 0);
	shape_change(d, 0);
	cof = 50;
	if (d->m_h> 15 && d->m_w > 15)
		cof = 25;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, (d->m_w *cof), (d->m_h *cof)+ cof, "Filler");
	mlx_string_put(mlx_ptr, win_ptr, 100, 30, GREEN, "Player1");
	mlx_string_put(mlx_ptr, win_ptr, 100, 50, GREEN, "my.filler");
	mlx_string_put(mlx_ptr, win_ptr, 950, 30, RED, "Player2");
	mlx_string_put(mlx_ptr, win_ptr, 950, 50, RED, "Evil");
	mlx_string_put(mlx_ptr, win_ptr, 500, 60, LIGHT_GR, "Winner is");
	//vertical;
	while (j < (d->m_w *cof))
	{
		i = (d->m_h *cof)/ 10;
		while (++i < (d->m_h *cof) + 80)
			mlx_pixel_put(mlx_ptr, win_ptr, j, i, COLOR_GRID);
		j += cof;
	}
	//horizontal
	i = (d->m_h *cof)/ 10;
	while (i < (d->m_h *cof) + cof)
	{
		j = 0;
		while (++j < (d->m_w *cof))
			mlx_pixel_put(mlx_ptr, win_ptr, j, i, COLOR_GRID);
		i += cof;
	}
	/*mlx_string_put(mlx_ptr, win_ptr, 10, 2 + 1 + (SCOREBOARD * 30) / 100,
			COLOR_P1A,"--------------");
	mlx_string_put(mlx_ptr, win_ptr, 10, 2 + 1 + (SCOREBOARD * 60) / 100,
			COLOR_P2A, "--------------");
	mlx_string_put(mlx_ptr, win_ptr, 200, 2 + 1 + (SCOREBOARD * 30) / 100,
			COLOR_GRID, "Esc to close");
	mlx_string_put(mlx_ptr, win_ptr, 200, 2 + 1 + (SCOREBOARD * 60) / 100,
			COLOR_GRID, "Space to pause 10 sec");
	//mlx_key_hook(win_ptr, deal_key, (void*)0);*/
	mlx_loop(mlx_ptr);
	return (0);
}
