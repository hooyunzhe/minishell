/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:56:49 by hyun-zhe          #+#    #+#             */
/*   Updated: 2021/06/06 20:10:20 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	i = -1;
	str = malloc((ft_strlen(s) * sizeof(char)) + 1);
	if (!str)
		return (NULL);
	while (s[++i])
		str[i] = (*f)(i, s[i]);
	str[i] = 0;
	return (str);
}
