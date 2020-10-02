/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 15:31:16 by lbagg             #+#    #+#             */
/*   Updated: 2020/06/11 16:49:47 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	del_element(t_descr **head, int fd)
{
	t_descr *tmp;
	t_descr *prev;

	prev = NULL;
	tmp = *head;
	if (tmp && (tmp->fd == fd))
	{
		*head = tmp->next;
		free(tmp->data);
		free(tmp);
		return ;
	}
	while (tmp)
	{
		prev = tmp;
		tmp = tmp->next;
		if (tmp->fd == fd)
		{
			prev->next = tmp->next;
			free(tmp->data);
			free(tmp);
			return ;
		}
	}
}

int		cut_line(char **tmp_rem, char **line, char *ch, char **remainder)
{
	char	*tmp;
	int		i;

	i = 0;
	if (ch)
	{
		while ((*tmp_rem)[i] != *ch)
			i++;
		if (!(*line = (char*)malloc(sizeof(char) * (i + 1))))
			return (-1);
		ft_strlcpy(*line, *tmp_rem, i + 1);
		ch++;
		if (!(tmp = ft_strdup(ch)))
			return (-1);
		ft_strlcpy(*remainder, tmp, ft_strlen(ch) + 1);
		free(tmp);
		return (1);
	}
	if (*tmp_rem)
		if (!(*line = ft_strdup(*tmp_rem)))
			return (-1);
	return (0);
}

int		read_file(int fd, char **remainder, char **line, char **ch)
{
	int		ret;
	char	*buf;
	char	*tmp_rem;
	int		res;
	char	*tmp;

	if (!(buf = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (!(tmp_rem = ft_strdup(*remainder)))
		return (-1);
	while (!*ch && (ret = read(fd, buf, BUFFER_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		tmp = tmp_rem;
		if (!(tmp_rem = ft_strjoin(tmp, buf)))
			return (-1);
		free(tmp);
		*ch = ft_strchr(tmp_rem, '\n');
	}
	free(buf);
	res = cut_line(&tmp_rem, line, *ch, remainder);
	free(tmp_rem);
	return (res);
}

t_descr	*new_list(int fd)
{
	t_descr	*new;
	int		i;

	i = 0;
	if (!(new = (t_descr*)malloc(sizeof(t_descr))))
		return (NULL);
	new->fd = fd;
	if (!(new->data = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (NULL);
	while (i <= BUFFER_SIZE)
	{
		(new->data)[i] = 0;
		i++;
	}
	new->next = NULL;
	return (new);
}

int		get_next_line(int fd, char **line)
{
	static t_descr	*list;
	t_descr			*tmp;
	int				out;
	char			*ch;

	ch = NULL;
	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (!list)
		if (!(list = new_list(fd)))
			return (-1);
	tmp = list;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
			if (!(tmp->next = new_list(fd)))
				return (-1);
		tmp = tmp->next;
	}
	ch = ft_strchr(tmp->data, '\n');
	if ((out = read_file(fd, &tmp->data, line, &ch)) <= 0)
		del_element(&list, tmp->fd);
	return (out);
}
