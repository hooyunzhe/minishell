/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:33:21 by hyun-zhe          #+#    #+#             */
/*   Updated: 2021/05/27 19:01:06 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	u_n;

	if (n < 0)
	{
		u_n = n * -1;
		ft_putchar_fd('-', fd);
	}
	else
		u_n = n;
	if (u_n > 9)
		ft_putnbr_fd(u_n / 10, fd);
	ft_putchar_fd((u_n % 10) + '0', fd);
}
