/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 09:11:38 by lbagg             #+#    #+#             */
/*   Updated: 2020/08/06 18:05:35 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 1

typedef struct		s_descr
{
	int				fd;
	char			*data;
	struct s_descr	*next;
}					t_descr;

int					get_next_line(int fd, char **line);
t_descr				*new_list(int fd);
int					read_file(int fd, char **remainder, char **line, char **ch);
int					cut_line(char **tmp_rem, char **line, char *ch,
char **remainder);
void				del_element(t_descr **head, int fd);
char				*ft_strchr(const char *s, int c);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);

#endif
