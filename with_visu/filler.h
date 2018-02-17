/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 16:29:00 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/06 16:29:02 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
#define FILLER_H 

#include "libft/libft.h"

typedef enum    e_way_definder
{
    right_down,
    left_down,
    right_up,
    left_up,
}               t_w_def;

typedef struct  s_coord
{
    int x;
    int y;
}               t_coords;

typedef struct s_data
{
    char **m;
    int m_h;
    int m_w;
    t_w_def way;
    char **sh;
    int sh_h;
    int sh_w;
    char s;
    int l_c;
    int l_r;
    int num_of_sign;
}               t_data;
#endif