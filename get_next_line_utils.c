/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfelguei <tfelguei.students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:50:47 by tfelguei          #+#    #+#             */
/*   Updated: 2024/08/28 17:31:03 by tfelguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoinx(char *s1, const char *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	new = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new)
		return (NULL);
	if (s1)
		ft_strlcpy(new, s1, len1 + 1);
	if (s2)
		ft_strlcpy(new + len1, s2, len2 + 1);
	return(new);
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
	char *copy;
	int i;

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