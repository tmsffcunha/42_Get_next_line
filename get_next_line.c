/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelguei <tfelguei.students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:30:20 by tfelguei          #+#    #+#             */
/*   Updated: 2024/08/28 17:36:48 by tfelguei         ###   ########.fr       */
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
	if (!ft_strchr(stash, '\n'))
		size = ft_strlen(stash);
	else
		size = ft_strlen(stash) - ft_strlen(ft_strchr(stash, '\n') + 1);
	line = (char *)malloc((size + 1) * sizeof(char));
	if (!line)
		return (free_data(NULL, stash)); // Free stash if malloc fails
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
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
	{
		stash = (char *)malloc(sizeof(char));
		if (!stash)
			return (NULL);
		*stash = 0;
	}
	stash = read_add(fd, stash);
	if (!stash)
		return (NULL);
	line = make_line(stash);
	if (!line)
		return (free_data(NULL, stash));	
	stash = new_stash(stash);
	if (!stash)
		return (free_data(NULL, line));
	return (line);
}
