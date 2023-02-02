/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: evoronin <evoronin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/19 18:19:09 by evoronin      #+#    #+#                 */
/*   Updated: 2023/02/01 13:09:00 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "get_next_line.h"
#include <limits.h>

char	*new_line(char *temp, char *newline)
{
	int	i;

	i = 0;
	while (temp[i] != '\n' && temp[i] != '\0')
	{
		newline[i] = temp[i];
		i++;
	}
	if (temp[i] == '\n')
	{
		newline[i] = '\n';
		i++;
	}
	newline[i] = '\0';
	return (newline);
}

char	*get_newline(char *temp)
{
	int		i;
	char	*newline;

	i = 0;
	while (temp[i] != '\n' && temp[i] != '\0')
		i++;
	if (temp[i] == '\n')
		newline = (char *)malloc(sizeof(char) * (i + 2));
	else
		newline = (char *)malloc(sizeof(char) * (i + 1));
	if (!newline)
		return (NULL);
	newline = new_line(temp, newline);
	if (!newline)
		return (free(newline), NULL);
	if (ft_strlen(newline) == 0)
		return (free(newline), NULL);
	return (newline);
}

char	*read_buf(int fd, char *temp)
{
	int			bytes;
	char		buf[BUFFER_SIZE + 1];

	bytes = 1;
	buf[0] = '\0';
	while (!ft_strchr(temp, '\n') && bytes != 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
			return (ft_free(&temp, NULL), NULL);
		buf[bytes] = '\0';
		temp = ft_strjoin(temp, buf);
		if (!temp)
		{
			buf[0] = '\0';
			return (ft_free(&temp, NULL), NULL);
		}
	}
	if (!temp)
		return (ft_free(&temp, NULL), NULL);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char		*temp;
	char			*line;

	if (!temp)
	{
		temp = (char *)malloc(sizeof(char) * 1);
		if (!temp)
			return (NULL);
		temp[0] = '\0';
	}
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	temp = read_buf(fd, temp);
	if (!temp)
		return (ft_free(&temp, NULL), NULL);
	line = get_newline(temp);
	if (!line)
		return (ft_free(&temp, NULL), NULL);
	temp = ft_temptrim(temp, line);
	if (!temp)
		return (ft_free(&temp, line), NULL);
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd;
// 	int		i;

// 	i = 1;
// 	fd = open("test1char.txt", O_RDONLY);
// 	while (i < 2)
// 	{
// 		line = get_next_line(fd);
// 		printf("[%d] %s", i, line);
// 		free(line);
// 		i++;
// 	}
// 	// system("leaks a.out");
// 	close(fd);
// 	return (0);
// }
