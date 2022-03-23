/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:30:27 by hyun-zhe          #+#    #+#             */
/*   Updated: 2021/06/10 01:32:08 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (!*needle || haystack == needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = i;
		k = 0;
		while (haystack[j] == needle[k] && j < len)
		{
			if (!needle[k + 1])
				return ((char *)&haystack[i]);
			j++;
			k++;
		}
		i++;
	}
	return (NULL);
}
