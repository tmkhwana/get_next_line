/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmkhwana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 14:59:36 by tmkhwana          #+#    #+#             */
/*   Updated: 2020/02/06 16:36:02 by tmkhwana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	search(char **line, char **str)
{
	char		*ptr;
	char		*ptr1;
	char		*q;

	ptr = *str;
	ptr1 = *str;
	q = ft_strchr(ptr, '\n');
	*line = ft_strsub(ptr, 0, q - ptr);
	while (*ptr)
		ptr++;
	q++;
	*str = ft_strsub(ptr1, q - ptr1, ptr - q);
	free(ptr1);
	return (1);
}
int		ft_short(char **line, char **str)
{
	if (*str && ft_strlen(*str) > 0)
	{
		*line = *str;
		*str = NULL;
		return (1);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char	*q[100];
	char		str[BUFF_SIZE + 1];
	char		*ptr;
	int		i;

	if (line && fd >= 0 && read(fd, str, 0) == 0)
	{
		if (q[fd] != NULL && ft_strchr(q[fd], '\n'))
			return (search(line, &q[fd]));
		while ((i = read(fd, str, BUFF_SIZE)) > 0)
		{
			if (q[fd] == NULL)
				q[fd] = ft_strdup("");
			str[i] = '\0';
			ptr = q[fd];
			q[fd] = ft_strjoin(ptr, str);
			free(ptr);
			if (ft_strchr(q[fd], '\n') != NULL)
				return (search(line, &q[fd]));
		}
		return (ft_short(line, &q[fd]));
	}
	return (-1);
}
