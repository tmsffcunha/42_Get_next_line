/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelguei <tfelguei.students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:50:47 by tfelguei          #+#    #+#             */
/*   Updated: 2024/07/17 19:57:55 by tfelguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoinx(char *s1, char const *s2)
{
	char	*new;
	char	*tmp;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	tmp = new;
	while (*s1)
		*tmp++ = *s1++;
	while (*s2)
		*tmp++ = *s2++;
	*tmp = 0;
	free(s1);
	s1 = NULL;
	return (new);
}

char	*ft_strchr(char *s, int c)
{
	unsigned char	new_c;

	new_c = (unsigned char)c;
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == new_c)
			return (s);
		s++;
	}
	if (*s == new_c)
		return (s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0 && dest)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	i = 0;
	while (src[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*copy;
	int		i;

	copy = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!(str) || !(copy))
		return (NULL);
	i = 0;
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}