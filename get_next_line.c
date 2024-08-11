/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelguei <tfelguei.students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:29:16 by tfelguei          #+#    #+#             */
/*   Updated: 2024/07/17 19:43:08 by tfelguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_data(char *buf, char *stash)
{
	if (buf)
		free(buf);
	if (stash)
		free(stash);
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
	int		read_size;

	read_size = 1;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	*buffer = 0;
	while (!ft_strchr(buffer, '\n') && read_size != 0)
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size < 0)
			return (free_data(buffer, stash));
		stash = ft_strjoinx(stash, buffer);
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
		stash = NULL;
		stash = (char *)malloc(sizeof(char));
		if (!stash)
			return (NULL);
		*stash = 0;
	}
	stash = read_add(fd, stash);
	line = make_line(stash);
	stash = new_stash(stash);
	return (line);
}
