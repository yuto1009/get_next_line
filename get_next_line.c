/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutoendo <yutoendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:41:05 by yuendo            #+#    #+#             */
/*   Updated: 2023/06/10 10:57:58 by yutoendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*loaded;
	char		*return_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	loaded = load_buffer(fd, loaded);
	if (!loaded)
		return (NULL);
	return_line = get_return_line(loaded);
	loaded = get_next_load(loaded);
	return (return_line);
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
//         if (line == NULL){
//             printf("LINE is NULL\n");
//             break ;
//         }
//         printf("%s", line);
//         free(line);
//     }
//     line = get_next_line(fd);

//     fd = open("./sample2", O_RDONLY);
//     while (1)
//     {
//         line = get_next_line(fd);
//         if (line == NULL){
//             printf("LINE is NULL\n");
//             return (0);
//         }
//         printf("%s", line);
//         free(line);
//     }
//     line = get_next_line(fd);
//     return (0);
// }