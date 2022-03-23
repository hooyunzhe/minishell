/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:13:17 by hyun-zhe          #+#    #+#             */
/*   Updated: 2021/06/21 18:50:51 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	is_num(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	size_t	longMax;
	size_t	num;
	int		sign;

	longMax = 9223372036854775807;
	num = 0;
	sign = 1;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (is_num(*str))
	{
		num *= 10;
		num += *str++ - '0';
		if (num > longMax)
			return (-1 + (sign == -1));
	}
	return (num * sign);
}
