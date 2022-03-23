/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:16:56 by hyun-zhe          #+#    #+#             */
/*   Updated: 2021/06/01 23:15:09 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_length(int n)
{
	int	len;

	len = 0 + (n <= 0);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*num;

	i = get_num_length(n);
	num = malloc((i * sizeof(char)) + 1);
	if (!num)
		return (NULL);
	num[i--] = 0;
	if (n < 0)
		num[0] = '-';
	if (n == 0)
		num[0] = '0';
	while (n != 0)
	{
		if (n > 0)
			num[i--] = (n % 10) + '0';
		else
			num[i--] = -1 * (n % 10) + '0';
		n /= 10;
	}
	return (num);
}
