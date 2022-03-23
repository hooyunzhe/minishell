/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 16:52:56 by hyun-zhe          #+#    #+#             */
/*   Updated: 2021/06/06 20:05:47 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	d_len;

	i = 0;
	d_len = ft_strlen(dst);
	if (dstsize == 0 || dstsize <= d_len)
		return (ft_strlen(src) + dstsize);
	while (src[i] && ((d_len + i + 1) < dstsize))
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = 0;
	return (d_len + ft_strlen(src));
}
