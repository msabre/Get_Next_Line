/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabre <msabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:14:40 by msabre            #+#    #+#             */
/*   Updated: 2019/10/19 20:49:20 by msabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

static t_list		*fd_find(t_list **list, int fd)
{
	t_list			*right_list;

	right_list = *list;
	while (right_list)
	{
		if (right_list->content_size == fd)
			break ;
		right_list = right_list->next;
	}
	if (right_list == NULL)
	{
		right_list = ft_lstnew("", fd);
		ft_lstadd(list, right_list);
	}
	return (right_list);
}

static int			ft_find_chr_in(char *buffer)
{
	int				i;

	i = 0;
	if (!buffer)
		return (-1);
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			return (i);
		}
		i++;
	}
	return (-1);
}

static int			ft_readline(int fd, t_list **list, char ***line)
{
	char			buffer[BUFF_SIZE + 1];
	char			*stat;
	int				i;

	while ((i = read(fd, buffer, BUFF_SIZE)))
	{
		buffer[i] = '\0';
		stat = (*list)->content;
		if ((i = ft_find_chr_in(buffer)) > -1)
		{
			**line = ft_strjoin((*list)->content, buffer);
			(*list)->content = ft_strdup(buffer + i + 1);
			ft_strdel(&stat);
			return (1);
		}
		(*list)->content = ft_strjoin((*list)->content, buffer);
		ft_strdel(&stat);
	}
	if ((*list)->content && (*list)->content[0] != '\0')
	{
		**line = ft_strdup((*list)->content);
		ft_strdel(&(*list)->content);
		return (1);
	}
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*list;
	t_list			*right_list;
	char			*mem[1];
	char			*stat;
	int				i;

	if (!line || fd < 0 || (read(fd, mem, 0)) < 0)
		return (-1);
	right_list = fd_find(&list, fd);
	if ((i = ft_find_chr_in(right_list->content)) > -1)
	{
		stat = right_list->content;
		*line = ft_strdup(right_list->content);
		right_list->content = ft_strdup(right_list->content + i + 1);
		ft_strdel(&stat);
		return (1);
	}
	i = ft_readline(fd, &right_list, &line);
	return (i);
}

int	main()
{
	int		fd;
	char	*buffer;
	char 	*mem;
	int		j;
	
	if((fd=open("Test.txt", O_RDONLY)) == -1)
		exit(1);
	while (get_next_line(fd, &buffer))
	{
	 	ft_putstr(buffer);
	 	ft_putchar('\n');
		ft_strdel(&buffer);
		j--;
	}
	return (0);
}
