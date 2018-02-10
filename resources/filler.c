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
	while(map[++i])
		free(map[i]);
	free(map);
}

void shape_free(char **shape)
{
	int i;
	
	i = -1;
	while(shape[++i])
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
	while(data->shape[i])
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
	int num_of_O;
	int i;
	int null_colmn;
	int stars_num;

	i = -1;
	num_of_O = 0;
	sh_coords->y = 0;
	sh_coords->x = 0;
	null_colmn = 0;
	stars_num = num_of_stars(data);
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
			null_colmn = sh_coords->x;
		if (data->map[data->last_row + sh_coords->y][data->last_colmn + sh_coords->x - null_colmn] == 'O' 
		|| data->map[data->last_row + sh_coords->y][data->last_colmn + sh_coords->x - null_colmn] == '.'
		|| data->map[data->last_row + sh_coords->y][data->last_colmn + sh_coords->x - null_colmn] == 'o')	
		{
			if (data->map[data->last_row + sh_coords->y][data->last_colmn + sh_coords->x - null_colmn] == 'O'
			|| data->map[data->last_row + sh_coords->y][data->last_colmn + sh_coords->x - null_colmn] == 'o')
				num_of_O++;
			if (num_of_O <= 1)
			{
				if (data->last_colmn + sh_coords->x - null_colmn >= 0)
					data->map[data->last_row + sh_coords->y][data->last_colmn + sh_coords->x - null_colmn] = ft_tolower((data->sign));
				sh_coords->x++;
			}
			else
				return (0);
		}
		else
			return (0);
	}
	if (data->last_colmn - null_colmn >= 0) 
		printf("%d %d\n",data->last_row, data->last_colmn - null_colmn);
	else
		return (2);
	data->last_row = data->last_row + sh_coords->y;
	data->last_colmn = data->last_colmn + sh_coords->x - 1 - null_colmn;
	return (1);
}

int play(t_data *data, t_coords *sh_coords)
{
	int i;
	int stars_num;
	
	i = 0;
	while(i != 1)
	{
		if ((i = ft_is_possible(data, sh_coords)) && i != 2)
			;
		else
		{
			if (data->last_colmn == 0)
			{
				
					data->last_row--;
				data->last_colmn = data->map_w - 2;
			}
			else if (data->last_colmn != 0)
				data->last_colmn--;
			/*while (data->last_row > 0 && data->map[data->last_row][data->last_colmn] != 'O')
			{
				if (data->last_colmn == 0)
				{
					if (data->last_row != 0)
						data->last_row--;
					data->last_colmn = data->map_w - 2;
				}
				else 
					data->last_colmn--;
			}*/
			if ((data->last_row == 0 && data->last_colmn == 0) || i == 2)
			{
				printf ("%d %d\n", 0, 0);
				return (2);
			}
		}
	}
	i = -1;
/*	while (data->map[++i])
		printf("%s\n", data->map[i]);
	i = -1;
	while (data->shape[++i])
		printf("%s\n", data->shape[i]);*/
		return (0);

}

void algo_defind(t_data *data, t_coords sign_c)
{
	if (sign_c.x < (data->map_w / 2) && sign_c.y < (data->map_h / 2))
		data->way = right_down;
	else if (sign_c.x > (data->map_w / 2) && sign_c.y < (data->map_h / 2))
		data->way = left_down; 
	else if (sign_c.x < (data->map_w / 2) && sign_c.y > (data->map_h / 2))
		data->way = right_up;
	else if (sign_c.x > (data->map_w / 2) && sign_c.y > (data->map_h / 2))
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
	data->last_colmn = sign_c.x;
	data->last_row = sign_c.y;
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
	i = -1;
	data->shape = (char**)malloc(sizeof(char*) * (data->sh_h + 1));
	while (++i < data->sh_h)
	{
		get_next_line(fd, &str);
		data->shape[i] = str;
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
	i = -1;
	data->map = (char**)malloc(sizeof(char*) * (data->map_h + 1));
	get_next_line(fd, &str);
	free(str);
	while (++i < data->map_h)
	{
		get_next_line(fd, &str);
		data->map[i] = ft_strsub(str, 4, data->map_w);
		free(str);
	}
	data->map[i] = NULL;
}
void init(t_data *data, int fd)
{
	char *str;
	int i;

	i = 7;
	str = NULL;
	map_change(data, fd);
	shape_change(data, fd);
	get_next_line(fd, &str);
	free(str);

}

int main(void)
{
	t_data *data;
	t_coords *sh_coords;
	t_w_def way;
	char *str;
	int fd;
	int i;

	fd = open("test", O_RDONLY);
	if (fd < 0)
		printf("Error\n");
	data = (t_data*)malloc(sizeof(t_data));
	sh_coords = (t_coords*)malloc(sizeof(t_coords));
	player_num(fd, data);
	init(data, fd);
	find_my_coords(data);
	//printf ("%d\n%d\n", data->last_colmn, data->last_row);
	while(play(data, sh_coords) != 2)
	{
		map_free(data->map);
		shape_free(data->shape);
		init(data, fd);
	}
	close(fd);
	return (0);
}
