/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum  <samatsum@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:58:51 by samatsum          #+#    #+#             */
/*   Updated: 2023/06/12 17:12:59 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char *save_fd)
{
	int		index;
	char	*next_line;

	index = 0;
	if (save_fd[index] == '\0')
		return (NULL);
	while (save_fd[index] != '\0' && save_fd[index] != '\n')
		index++;
	next_line = (char *)malloc(sizeof(char) * (index + 2));
	if (next_line == NULL)
		return (NULL);
	index = 0;
	while (save_fd[index] != '\0' && save_fd[index] != '\n')
	{
		next_line[index] = save_fd[index];
		index++;
	}
	if (save_fd[index] == '\n')
	{
		next_line[index] = save_fd[index];
		index++;
	}
	next_line[index] = '\0';
	return (next_line);
}

char	*ft_save_fd(char *save_fd)
{
	int		index;
	int		c;
	char	*next_save;

	index = 0;
	while (save_fd[index] != '\0' && save_fd[index] != '\n')
		index++;
	if (save_fd[index] == '\0')
	{
		free(save_fd);
		return (NULL);
	}
	next_save = (char *)malloc(sizeof(char) * (ft_strlen(save_fd) - index + 1));
	if (next_save == NULL)
	{
		free(save_fd);
		return (NULL);
	}
	index++;
	c = 0;
	while (save_fd[index] != '\0')
		next_save[c++] = save_fd[index++];
	next_save[c] = '\0';
	free(save_fd);
	return (next_save);
}

char	*ft_read_and_save_fd(int fd, char *save_fd)
{
	char	*buffer;
	ssize_t	readed_bytes;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	readed_bytes = 1;
	while (ft_strchr(save_fd, '\n') == NULL && readed_bytes != 0)
	{
		readed_bytes = read(fd, buffer, BUFFER_SIZE);
		if (readed_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[readed_bytes] = '\0';
		save_fd = ft_strjoin(save_fd, buffer);
	}
	free(buffer);
	return (save_fd);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[OPEN_MAX + 1];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	save[fd] = ft_read_and_save_fd(fd, save[fd]);
	if (save[fd] == NULL)
		return (NULL);
	line = ft_get_line(save[fd]);
	save[fd] = ft_save_fd(save[fd]);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int	main(void)
// {
// 	ssize_t	fd;
// 	char	*gnl;

// 	fd = open("test.txt", O_RDONLY);
// 	printf("fd = %zd\n",fd);
// 	gnl = "OK!";
// 	while (gnl)
// 	{
// 		gnl = get_next_line(fd);
// 		if (gnl != NULL)
// 		{
// 			printf("%s", gnl);
// 			free(gnl);
// 		}
// 		else if (gnl == NULL)
// 		{
// 			printf("(null)");
// 		}
// 	}
// 	close(fd);
// 	return (0);
// }
