/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutoendo <yutoendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:41:05 by yuendo            #+#    #+#             */
/*   Updated: 2023/06/02 17:27:12 by yutoendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd){
    char *buffer;
    size_t buffer_index;
    ssize_t reading_status;

    buffer = (char *)malloc(BUFFER_SIZE*sizeof(char)+1);   
    if (!buffer)
        return (NULL);
    buffer_index = 0;
    while(buffer_index < BUFFER_SIZE){
        reading_status = read(fd, &buffer[buffer_index], 1);
        if (reading_status == -1){   
            free(buffer);
            return (NULL);
        }
        else if (reading_status == 0)  
            break;
        if (buffer[buffer_index] == '\n'){
            buffer_index++;
            break;
        }
        buffer_index++;
    }
    buffer[buffer_index] = '\0';
    return buffer;
}

#include <fcntl.h>
#include <stdio.h>
int main()
{
    int        fd;
    char    *line;

    fd = open("./test/first_file", O_RDONLY);
    while (1)
    {
        line = get_next_line(fd);
        close (fd);
        if (line == NULL)
            break;
        printf("%s", line);
        free(line);
    }
    system("leaks a.out");
    return (0);
}