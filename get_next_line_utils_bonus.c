/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: evoronin <evoronin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 15:55:47 by evoronin      #+#    #+#                 */
/*   Updated: 2023/02/01 12:38:36 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = 0;
	while (str[i] != (char) c && str[i])
	{
		i++;
	}
	if (str[i] == (char) c)
		return (&str[i]);
	return (NULL);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *temp, char *buff)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!temp || !buff)
		return (ft_free(&temp, buff), NULL);
	res = malloc(sizeof(char) * (ft_strlen(temp) + ft_strlen(buff) + 1));
	if (!res)
		return (free(temp), NULL);
	while (temp[i] != '\0')
	{
		res[i] = temp[i];
		i++;
	}
	while (buff[j] != '\0')
	{
		res[i] = buff[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (free(temp), res);
}

char	*ft_temptrim(char *temp, char *line)
{
	char	*res;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = ft_strlen(temp);
	while (line[i] != 0)
		i++;
	res = (char *)malloc(sizeof(char) * (size - i + 2));
	if (!res)
		return (ft_free(&temp, NULL), NULL);
	while (temp[i] != '\0' && i < size)
	{
		res[j] = temp[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (free(temp), res);
}

char	*ft_free(char **str, char *str1)
{
	free(*str);
	free(str1);
	*str = NULL;
	return (NULL);
}
