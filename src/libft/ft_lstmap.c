/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 17:28:57 by hyun-zhe          #+#    #+#             */
/*   Updated: 2021/06/02 00:25:54 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*temp;

	if (!lst || !f)
		return (NULL);
	newlst = ft_lstnew((*f)(lst->content));
	temp = newlst;
	lst = lst->next;
	while (lst && newlst)
	{
		newlst->next = ft_lstnew((*f)(lst->content));
		if (!newlst->next)
			ft_lstclear(&temp, del);
		newlst = newlst->next;
		lst = lst->next;
	}
	return (temp);
}
