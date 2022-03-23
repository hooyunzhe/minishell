/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 18:33:43 by hyun-zhe          #+#    #+#             */
/*   Updated: 2021/06/10 00:25:28 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;

	str = NULL;
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			str = (char *)s;
		s++;
	}
	if (c == 0)
		return ((char *)s);
	else
		return (str);
}
