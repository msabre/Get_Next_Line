/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabre <msabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:35:13 by msabre            #+#    #+#             */
/*   Updated: 2019/04/17 18:08:28 by msabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*ptr;
	t_list	*ptr_next;

	ptr = *alst;
	while (ptr != NULL)
	{
		ptr_next = ptr->next;
		del(ptr->content, ptr->content_size);
		ptr = ptr_next;
	}
	free(ptr);
	free((*alst)->next);
	*alst = NULL;
}
