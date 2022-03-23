/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:28:23 by hyun-zhe          #+#    #+#             */
/*   Updated: 2021/06/06 20:37:49 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_set(char c, const char *set)
{
	if (set)
	{
		while (*set)
		{
			if (c == *set++)
				return (1);
		}
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		start;
	int		end;
	char	*newstr;

	if (!s1)
		return (NULL);
	i = 0;
	start = -1;
	end = ft_strlen(s1);
	while (++start < end && char_in_set(s1[start], set))
		;
	while (--end >= 0 && char_in_set(s1[end], set))
		;
	newstr = malloc(((end > 0) * (end - start + 1) * sizeof(char)) + 1);
	if (!newstr)
		return (NULL);
	while (start <= end)
		newstr[i++] = s1[start++];
	newstr[i] = 0;
	return (newstr);
}
