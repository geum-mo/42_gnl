/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekang <gekang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:24:09 by gekang            #+#    #+#             */
/*   Updated: 2021/03/05 07:08:38 by gekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					find_nl(char *str)
{
	int				i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int					divide_line(char **buf_dup, char **line, int cutoff_idx)
{
	char			*tmp;
	int				len;

	(*buf_dup)[cutoff_idx] = '\0';
	*line = ft_strdup(*buf_dup);
	len = ft_strlen(*buf_dup + cutoff_idx + 1);
	if (len == 0)
	{
		free(*buf_dup);
		*buf_dup = 0;
		return (1);
	}
	tmp = ft_strdup(*buf_dup + cutoff_idx + 1);
	free(*buf_dup);
	*buf_dup = tmp;
	return (1);
}

int					end_process(char **buf_dup, char **line, int read_size)
{
	int				cutoff_idx;

	if (read_size < 0)
		return (-1);
	if (*buf_dup && (cutoff_idx = find_nl(*buf_dup)) >= 0)
		return (divide_line(buf_dup, line, cutoff_idx));
	else if (*buf_dup)
	{
		*line = *buf_dup;
		*buf_dup = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int					get_next_line(int fd, char **line)
{
	int				cutoff_idx;
	int				bytes_read;
	char			buf[BUFFER_SIZE + 1];
	static char		*buf_dup[OPEN_MAX];

	if ((fd < 0) || !line || (BUFFER_SIZE <= 0))
		return (-1);
	while ((bytes_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bytes_read] = '\0';
		buf_dup[fd] = ft_strjoin(buf_dup[fd], buf);
		if ((cutoff_idx = find_nl(buf_dup[fd])) >= 0)
			return (divide_line(&buf_dup[fd], line, cutoff_idx));
	}
	return (end_process(&buf_dup[fd], line, bytes_read));
}
