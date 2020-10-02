/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 11:12:02 by lbagg             #+#    #+#             */
/*   Updated: 2020/06/08 18:44:55 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>

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
