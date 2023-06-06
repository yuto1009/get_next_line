/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutoendo <yutoendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:41:05 by yuendo            #+#    #+#             */
/*   Updated: 2023/06/06 22:19:20 by yutoendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	ssize;

	str = (char *)s;
	ssize = ft_strlen(str);
	if (str[ssize] == (char)c)
		return (&str[ssize]);
	while (ssize--)
	{
		if (str[ssize] == (char)c)
			return (&str[ssize]);
	}
	return (NULL);
}

char	*my_strjoin(char *s1, char *s2)
{
	char	*str;
	char	*str_start;

	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1)*sizeof(char));
	if (!str)
		return (NULL);
	str_start = str;
	while (*s1)
		*str++ = *s1++;
    free(s1);
	while (*s2)
		*str++ = *s2++;
	*str = 0;
	return (str_start);
}

static char *load_buffer(int fd, char *loaded){
    char *buffer;
    ssize_t loaded_bytes;

    buffer = (char *)malloc((BUFFER_SIZE + 1)*sizeof(char));
    if(!buffer)
        return NULL;
    loaded_bytes = 1;
    while(!ft_strrchr(loaded, '\n') && loaded_bytes != 0){
        loaded_bytes = read(fd, buffer, BUFFER_SIZE);
        if(loaded_bytes == -1){
            free(buffer);
            return NULL;
        }
        buffer[loaded_bytes] = '\0';
        loaded = my_strjoin(loaded, buffer);
    }
    free(buffer);
    return loaded;
}

char *get_return_line(char *loaded){
    size_t i;
    char *return_line;
    
    i = 0;
    while(loaded[i] && loaded[i] != '\n')
        i++;
    if(loaded[i] && loaded[i] == '\n')
        i++;
    return_line = (char *)malloc((i+1)*sizeof(char));
    if(!return_line)
        return NULL;
    i = 0;
    while(loaded[i] && loaded[i] != '\n'){
        return_line[i] = loaded[i];
        i++;
    }
    if(loaded[i] && loaded[i] == '\n'){
        return_line[i] = loaded[i];
        i++;
    }
    return_line[i] = '\0';
    return(return_line);
}

char *get_next_load(char *loaded){
    char *next_load;
    size_t i;
    size_t next_load_bytes;

    i = 0;
    while(loaded[i] && loaded[i] != '\n')
        i++;
    if(loaded[i] && loaded[i] == '\n')
        i++;
    next_load_bytes = 0;
    while(loaded[i]){
        i++;
        next_load_bytes++;
    }
    next_load = (char *)malloc((next_load_bytes+1)*sizeof(char));
    if(!next_load)
        return NULL;
    i = i - next_load_bytes;
    while(i < next_load_bytes)
        *next_load++ = loaded[i++];
    return next_load;
}

char *get_next_line(int fd){
    static char *loaded = "\0";
    static int last_fd = -1;
    char *return_line;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    if (last_fd != fd)
        *loaded = '\0';
    loaded = load_buffer(fd, loaded);
    return_line = get_return_line(loaded);
    // save what's left of loaded for next call
    loaded = get_next_load(loaded);
    return return_line;
}
// #include <fcntl.h>
// #include <stdio.h>
// int main()
// {
//     int        fd;
//     char    *line;

//     fd = open("./sample", O_RDONLY);
//     while (1)
//     {
//         line = get_next_line(fd);
//         close (fd);
//         if (line == NULL){
//             printf("LINE is NULL\n");
//             return 0;
//         }
//         printf("%s", line);
//         free(line);
//     }
//     // system("leaks a.out");
//     return (0);
// }