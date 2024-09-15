/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:41:52 by dmathis           #+#    #+#             */
/*   Updated: 2024/05/30 08:58:42 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_error(char *big_buff, char *read_buff)
{
	free(big_buff);
	if (!read_buff)
		return (NULL);
	free(read_buff);
	return (NULL);
}

static char	*get_line(char *big_buff)
{
	char	*str;
	int		i;

	i = 0;
	if (!big_buff[i])
		return (NULL);
	while (big_buff[i] && big_buff[i] != '\n')
		i++;
	if (big_buff[i] == '\n')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i] = big_buff[i];
		i--;
	}
	return (str);
}

char	*get_next_buff(char *big_buff)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (big_buff[i] && big_buff[i] != '\n')
		i++;
	if (!big_buff[i])
		return (ft_error(big_buff, 0));
	result = malloc((ft_strlen(big_buff) - i + 1) * sizeof(char));
	if (!result)
		return (ft_error(big_buff, 0));
	i++;
	while (big_buff[i])
		result[j++] = big_buff[i++];
	result[j] = 0;
	free(big_buff);
	return (result);
}

char	*ft_get_all_text(int fd, char *big_buff)
{
	int		status;
	char	*read_buff;
	char	*temp;

	status = 1;
	read_buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!read_buff)
		return (ft_error(big_buff, 0));
	while (status)
	{
		status = read(fd, read_buff, BUFFER_SIZE);
		if (status == -1)
			return (ft_error(big_buff, read_buff));
		read_buff[status] = '\0';
		temp = ft_strjoin(big_buff, read_buff);
		free(big_buff);
		big_buff = temp;
		if (!big_buff)
			return (ft_error(read_buff, 0));
		if (ft_strchr(read_buff, '\n'))
			break ;
	}
	free(read_buff);
	return (big_buff);
}

char	*get_next_line(int fd)
{
	static char	*big_buff[1025];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!big_buff[fd])
		big_buff[fd] = ft_calloc(1, sizeof(char));
	if (!big_buff[fd])
		return (NULL);
	big_buff[fd] = ft_get_all_text(fd, big_buff[fd]);
	if (!big_buff[fd])
		return (NULL);
	line = get_line(big_buff[fd]);
	if (!line)
	{
		free(big_buff[fd]);
		big_buff[fd] = 0;
		return (NULL);
	}
	big_buff[fd] = get_next_buff(big_buff[fd]);
	return (line);
}
