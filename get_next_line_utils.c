/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutoendo <yutoendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:41:45 by yuendo            #+#    #+#             */
/*   Updated: 2023/06/10 11:01:10 by yutoendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
		*p++ = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	p = (void *)malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}

char	*my_strchr(const char *s, int c)
{
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	while (*str != '\0')
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	if (*str == (char)c)
		return (str);
	return (NULL);
}

char	*my_strjoin(char *loaded, char *buffer)
{
	char	*str;
	char	*str_start;
	char	*loaded_start;

	if (!loaded)
		loaded = (char *)ft_calloc(1, sizeof(char));
	if (!loaded || !buffer)
		return (NULL);
	str = (char *)malloc((ft_strlen(loaded) + ft_strlen(buffer) + 1)
			* sizeof(char));
	if (!str)
		return (NULL);
	str_start = str;
	loaded_start = loaded;
	while (*loaded)
		*str++ = *loaded++;
	while (*buffer)
		*str++ = *buffer++;
	*str = 0;
	free(loaded_start);
	return (str_start);
}

char	*load_buffer(int fd, char *loaded)
{
	char	*buffer;
	ssize_t	loaded_bytes;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	loaded_bytes = 1;
	while (!my_strchr(loaded, '\n') && loaded_bytes != 0)
	{
		loaded_bytes = read(fd, buffer, BUFFER_SIZE);
		if (loaded_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[loaded_bytes] = '\0';
		loaded = my_strjoin(loaded, buffer);
	}
	free(buffer);
	return (loaded);
}

char	*get_return_line(char *loaded)
{
	size_t	i;
	char	*return_line;

	i = 0;
	if (!*loaded)
		return (NULL);
	while (loaded[i] && loaded[i] != '\n')
		i++;
	if (loaded[i] && loaded[i] == '\n')
		i++;
	return_line = (char *)malloc((i + 1) * sizeof(char));
	if (!return_line)
		return (NULL);
	i = 0;
	while (loaded[i] && loaded[i] != '\n')
	{
		return_line[i] = loaded[i];
		i++;
	}
	if (loaded[i] && loaded[i] == '\n')
	{
		return_line[i] = loaded[i];
		i++;
	}
	return_line[i] = '\0';
	return (return_line);
}

char	*get_next_load(char *loaded)
{
	char	*next_load;
	size_t	i;
	size_t	j;

	i = 0;
	while (loaded[i] && loaded[i] != '\n')
		i++;
	if (!loaded[i])
	{
		free(loaded);
		return (NULL);
	}
	next_load = (char *)malloc((ft_strlen(loaded) - i + 1) * sizeof(char));
	if (!next_load)
		return (NULL);
	i++;
	j = 0;
	while (loaded[i])
		next_load[j++] = loaded[i++];
	next_load[j] = '\0';
	free(loaded);
	return (next_load);
}
