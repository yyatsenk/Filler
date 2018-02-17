/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_create_elem.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 11:36:20 by yyatsenk          #+#    #+#             */
/*   Updated: 2017/11/05 11:36:22 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_whiteskip(char **str)
{
	while (**str == '\t' || **str == '\n' || **str == '\v'
	|| **str == '\f' || **str == '\r' || **str == ' ')
		*str = *str + 1;
}