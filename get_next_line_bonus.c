/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelguei <tfelguei.students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 20:06:06 by tfelguei          #+#    #+#             */
/*   Updated: 2024/08/29 20:15:55 by tfelguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_data(char *buf, char *stash)
{
	if (buf)
	{
		free(buf);
		buf = NULL;
	}
	if (stash)
	{
		free(stash);
		stash = NULL;
	}
	return (NULL);
}

static char	*new_stash(char *stash)
{
	char	*new_stash;

	if (!stash)
		return (NULL);
	if (!ft_strchr(stash, '\n'))
		return (free_data(NULL, stash));
	new_stash = ft_strdup(ft_strchr(stash, '\n') + 1);
	if (!new_stash)
		return (free_data(NULL, stash));
	free(stash);
	stash = NULL;
	return (new_stash);
}

static char	*make_line(char *stash)
{
	char	*line;
	size_t	size;

	if (!stash)
		return (NULL);
	if (!*stash)
		return (free_data(NULL, stash));
	if (!ft_strchr(stash, '\n'))
		size = ft_strlen(stash);
	else
		size = ft_strlen(stash) - ft_strlen(ft_strchr(stash, '\n') + 1);
	line = (char *)malloc((size + 1) * sizeof(char));
	if (!line)
		return (free_data(NULL, stash));
	ft_strlcpy(line, stash, size + 1);
	return (line);
}

static char	*read_add(int fd, char *stash)
{
	char	*buffer;
	char	*new_stash;
	int		read_size;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free_data(NULL, stash));
	read_size = 1;
	while (!ft_strchr(stash, '\n') && read_size != 0)
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size < 0)
			return (free_data(buffer, stash));
		buffer[read_size] = '\0';
		new_stash = ft_strjoinx(stash, buffer);
		free(stash);
		stash = new_stash;
		if (!stash)
			return (free_data(buffer, NULL));
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd])
	{
		stash[fd] = NULL;
		stash[fd] = (char *)malloc(sizeof(char));
		if (!stash[fd])
			return (NULL);
		*stash[fd] = 0;
	}
	stash[fd] = read_add(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = make_line(stash[fd]);
	if (!line)
		return (NULL);
	stash[fd] = new_stash(stash[fd]);
	if (!stash[fd] && !line)
		return (free_data(NULL, line));
	return (line);
}
