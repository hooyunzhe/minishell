/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:40:57 by hyun-zhe          #+#    #+#             */
/*   Updated: 2021/06/06 19:21:34 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*m_block;

	i = 0;
	m_block = malloc(count * size);
	if (!m_block)
		return (NULL);
	ft_bzero(m_block, count * size);
	return ((void *)m_block);
}
