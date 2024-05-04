/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blozano- <blozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:59:16 by blozano-          #+#    #+#             */
/*   Updated: 2024/03/10 20:24:25 by blozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	read_error(char **static_buff, char **buffer, int bytes)
{
	if (bytes == -1)
	{
		free(*static_buff);
		free(*buffer);
		*static_buff = NULL;
		*buffer = NULL;
	}
}

int	ft_find_nl(char *s)
{
	unsigned int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (-1);
	return (i);
}

char	*ft_create_line(char *buf_static, int index)
{
	char	*line;
	int		i;

	line = (char *)malloc((index + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buf_static[i] != '\n')
	{
		line[i] = buf_static[i];
		i++;
	}
	line[i] = '\n';
	line[i + 1] = '\0';
	return (line);
}

char	*ft_calc_line(char *buf_static)
{
	char	*line;
	int		index;

	if (ft_strlen(buf_static) <= 0)
		return (NULL);
	index = ft_find_nl(buf_static);
	if (index == -1 || index == ((int)ft_strlen(buf_static) - 1))
	{
		line = ft_strdup(buf_static);
		return (line);
	}
	line = ft_create_line(buf_static, index);
	return (line);
}

char	*ft_calc_buf(char	*buf_static)
{
	int				index;
	unsigned int	buf_len;

	if (!buf_static)
		return (NULL);
	buf_len = ft_strlen(buf_static);
	index = ft_find_nl(buf_static);
	if (index == -1 || ((buf_len - index) == 1))
	{
		free(buf_static);
		return (NULL);
	}
	buf_static = ft_substr(buf_static, (index + 1), (buf_len - index - 1));
	return (buf_static);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	int			bytes;
	static char	*buf_static;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (ft_find_nl(buf_static) == -1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buffer[bytes] = '\0';
		buf_static = ft_strjoin(buf_static, buffer);
	}
	free(buffer);
	if (bytes == -1)
		return (ft_bzero(buf_static, ft_strlen(buf_static)), NULL);
	line = ft_calc_line(buf_static);
	buf_static = ft_calc_buf(buf_static);
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*camino;
	char	*str;
	int 	i;

	camino = "test.txt";
	fd = open(camino, O_RDONLY);// 
	O_RDONLY se utiliza para abrir 
	un archivo en modo de solo lectura,
	i = 0;
	while(i < 6)
	{
		str = get_next_line(fd);
		printf("%s", str);
		i++;
	}
}
*/
