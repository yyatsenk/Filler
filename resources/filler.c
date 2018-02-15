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
 
void map_free(char **map)
{
	int i;

	i = -1;
	while(map && map[++i])
		free(map[i]);
	free(map[i]);
	free(map);
}

void shape_free(char **shape)
{
	int i;
	
	i = -1;
	while(shape && shape[++i])
		free(shape[i]);
	free(shape[i]);
	free(shape);
}

int num_of_stars(t_data *data)
{
	int stars;
	int i;
	int j;

	stars = 0;
	i = 0;
	while(data->shape && data->shape[i])
	{
		j = 0;
		while(data->shape[i][j])
		{
			if (data->shape[i][j] == '*')
				stars++;
			j++;
		}
		i++;
	}
	return (stars);
}


int ft_is_possible(t_data *data, t_coords *sh_coords)
{
	int num_of_sign;
	int i;
	int null_colmn;
	int null_row;
	char enemy;
	int stars_num;

	i = -1;
	num_of_sign = 0;
	sh_coords->y = 0;
	sh_coords->x = 0;
	null_colmn = 0;
	null_row = 0;
	stars_num = num_of_stars(data);
	if (data->sign == 'O')
		enemy = 'X';
	else
		enemy = 'O';
	if ((data->last_colmn + data->sh_w) >= data->map_w
	|| (data->last_row + data->sh_h) >= data->map_h)
		return (0);
	while (++i < stars_num)
	{
		while(data->shape[sh_coords->y] && data->shape[sh_coords->y][sh_coords->x] != '*')
		{
			sh_coords->x++;
			if (data->shape[sh_coords->y][sh_coords->x] == '\0')
			{
					sh_coords->y++;
					sh_coords->x = 0;
			}
		}
		if (data->shape[sh_coords->y][sh_coords->x] == '*' && i == 0)
		{
			null_colmn = sh_coords->x;
			null_row = sh_coords->y;
		}
		if ((data->last_colmn + sh_coords->x - null_colmn) >= 0 && (data->last_row + sh_coords->y - null_row)>=0 
		&& (data->last_colmn + sh_coords->x - null_colmn) <= (data->map_w -1) && (data->last_row + sh_coords->y - null_row)<= (data->map_h -1)
		&&(data->map[data->last_row + sh_coords->y - null_row][data->last_colmn + sh_coords->x - null_colmn] == data->sign 
		|| data->map[data->last_row + sh_coords->y - null_row][data->last_colmn + sh_coords->x - null_colmn] == '.'
		|| data->map[data->last_row + sh_coords->y - null_row][data->last_colmn + sh_coords->x - null_colmn] == ft_tolower(data->sign)) 
		&& data->map[data->last_row + sh_coords->y - null_row][data->last_colmn + sh_coords->x - null_colmn] != enemy 
		&& data->map[data->last_row + sh_coords->y - null_row][data->last_colmn + sh_coords->x - null_colmn] != ft_tolower(enemy))	
		{
			if ((data->map[data->last_row + sh_coords->y - null_row][data->last_colmn + sh_coords->x - null_colmn] == data->sign 
			|| data->map[data->last_row + sh_coords->y - null_row][data->last_colmn + sh_coords->x - null_colmn] == ft_tolower(data->sign)))
				num_of_sign++;
			if (data->shape[sh_coords->y][sh_coords->x + 1] == '\0')
			{
					sh_coords->y++;
					sh_coords->x = 0;
			}
			else
				sh_coords->x++;
		}
		else
			return (0);
	}
	if (num_of_sign != 1)
		return (0);
	if (data->last_colmn - null_colmn < 0 || data->last_row - null_row < 0)
		return (0);
	data->last_colmn = data->last_colmn - null_colmn;
	data->last_row = data->last_row - null_row;
	return (1);
}

int play0(t_data *data, t_coords *sh_coords)
{
	int i;
	
	i = 0;
	data->last_colmn = data->map_w - 1;
	data->last_row = data->map_h - 1;
	while(i != 1)
	{
		if ((i = ft_is_possible(data, sh_coords)))
			ft_printf("%d %d\n", data->last_row, data->last_colmn);
		else
		{
			if ((data->last_row == 0 && data->last_colmn == 0))
			{
				ft_printf ("%d %d\n", 0, 0);
				return (0);
			}
			else if (data->last_colmn == 0 && data->last_row > 0 && (data->last_colmn = data->map_w - 1))			
				data->last_row--;
			else if (data->last_colmn != 0)
				data->last_colmn--;
		}
	}
		return (1);
}

int play1(t_data *data, t_coords *sh_coords)
{
	int i;
	
	i = 0;
	data->last_colmn = 0;
	data->last_row = 0;
	while(i != 1)
	{
		if ((i = ft_is_possible(data, sh_coords)))
			ft_printf("%d %d\n", data->last_row, data->last_colmn);
		else
		{
			if ((data->last_row == (data->map_h - 1) && data->last_colmn == (data->map_w - 1)))
			{
				ft_printf ("%d %d\n", 0, 0);
				return (0);
			}
			if (data->last_colmn == (data->map_w - 1) 
				&& data->last_row < (data->map_h - 1) && !(data->last_colmn = 0))
				data->last_row++;
			else if (data->last_colmn != (data->map_w - 1))
				data->last_colmn++;
		}
	}
	return (1);

}

void algo_defind(t_data *data, t_coords sign_c)
{
	if (sign_c.x < (data->map_w / 2) && sign_c.y < (data->map_h / 2))
		data->way = right_down;
	else if (sign_c.x > (data->map_w / 2) && sign_c.y < (data->map_h / 2))
		data->way = left_down; 
	else if (sign_c.x < (data->map_w / 2) && sign_c.y > (data->map_h / 2))
		data->way = right_up;
	else if (sign_c.x > (data->map_w / 2) && sign_c.y >= (data->map_h / 2))
		data->way = left_up;
}

void find_my_coords(t_data *data)
{
	t_coords map;
	t_coords sign_c;

	map.y = 0;
	while(map.y < data->map_h)
	{
		map.x = 0;
		while (map.x < data->map_w)
		{
			if (data->map[map.y][map.x] == data->sign)
			{
					sign_c.x = map.x;
					sign_c.y = map.y;
			}
			map.x++;
		}
		map.y++;
	}
	algo_defind(data, sign_c);
}
void shape_change(t_data *data, int fd)
{
	int i;
	char *str;

	i = 5;
	get_next_line(fd, &str);
	data->sh_h = ft_atoi(&str[i]);
	while (ft_isdigit(str[++i]))
		;
	data->sh_w = ft_atoi(&str[i]);
	free(str);
	i = -1;
	data->shape = (char**)malloc(sizeof(char*) * (data->sh_h + 1));
	if (data->shape == NULL)
	{
		ft_printf("0 0\n");
		exit(1);
	}
	while (++i < data->sh_h)
	{
		get_next_line(fd, &str);
		data->shape[i] = ft_strdup(str);
		free(str);
	}
	data->shape[i] = NULL;
}

void player_num(int fd, t_data *data)
{
	char *str;
	str = NULL;
	get_next_line(fd, &str);
	if (str && str[10] == '1')
		data->sign = 'O';
	else if (str && str[10] == '2')
		data->sign = 'X';
	free(str);
}

void map_change(t_data *data, int fd)
{
	char *str;
	int i;

	str = NULL;
	i = 7;
	get_next_line(fd, &str);
	data->map_h = ft_atoi(&str[i]);
	while (ft_isdigit(str[++i]))
		;
	data->map_w = ft_atoi(&str[i]);
	free(str);
	i = -1;
	data->map = (char**)malloc(sizeof(char*) * (data->map_h + 1));
	if (data->map == NULL)
	{
		ft_printf("0 0\n");
		exit(1);
	}
	get_next_line(fd, &str);
	free(str);
	while (++i < data->map_h)
	{
		get_next_line(fd, &str);
		data->map[i] = ft_strsub(str, 4, data->map_w);
		if (data->map[i] == NULL)
		{
			ft_printf("0 0\n");
			exit(1);
		}
		free(str);
	}
	data->map[i] = NULL;
}
void init(t_data *data, int fd)
{
	map_change(data, fd);
	shape_change(data, fd);
}
void algo0(t_data *data, t_coords *sh_coords, int fd)
{
	while(play0(data, sh_coords))
	{
		map_free(data->map);
		shape_free(data->shape);
		init(data, fd);
	}
}
void algo1(t_data *data, t_coords *sh_coords, int fd)
{	
	while(play1(data, sh_coords))
	{
		map_free(data->map);
		shape_free(data->shape);
		init(data, fd);
	}
}
int main(void)
{
	t_data *data;
	t_coords *sh_coords;

	data = (t_data*)malloc(sizeof(t_data));
	sh_coords = (t_coords*)malloc(sizeof(t_coords));
	player_num(0, data);
	init(data, 0);
	find_my_coords(data);
	if (data->way == 1 || data->way == 0)
		algo0(data, sh_coords,0);
	else
		algo1(data, sh_coords, 0);
	map_free(data->map);
	shape_free(data->shape);
	free(data);
	free(sh_coords);
	return (0);
}
