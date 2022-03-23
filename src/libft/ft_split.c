/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 17:04:58 by hyun-zhe          #+#    #+#             */
/*   Updated: 2021/06/06 20:08:49 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_length(const char *s, char c)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (s[++i])
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
			len++;
	}
	return (len);
}

static char	*get_word(const char *s, int pos, int len, int last)
{
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = pos - len;
	word = malloc(((len + last) * sizeof(char)) + 1);
	while (j < (pos + last))
		word[i++] = s[j++];
	word[i] = 0;
	return (word);
}

char	**ft_split(const char *s, char c)
{
	int		w;
	int		i;
	int		len;
	char	**strs;

	if (!s)
		return (NULL);
	w = 0;
	i = -1;
	len = 0;
	strs = malloc((get_length(s, c) + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (s[++i])
	{
		if ((len > 0 && s[i] == c) || (!s[i + 1] && s[i] != c))
		{
			strs[w++] = get_word(s, i, len, s[i] != c);
			len = 0;
		}
		else if (s[i] != c)
			len++;
	}
	strs[w] = NULL;
	return (strs);
}
