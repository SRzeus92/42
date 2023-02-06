/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgolino <fgolino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:17:39 by fgolino           #+#    #+#             */
/*   Updated: 2023/02/06 16:09:26 by fgolino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*line_parsing(char	*str, int fd)
{
	int		i;
	char	*line;
	t_bool	check;
	char	*whatever;

	i = 0;
	check = FALSE;
	whatever = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	while (i < BUFFER_SIZE)
	{
		if (str[i] == '\n' || str[i] == '\0')
		{
			line = ft_substr(str, 0, (i + 1));
			check = TRUE;
			i = BUFFER_SIZE; 
		}
		i++;
	}
	if (check == FALSE)
	{
		read(fd, whatever, BUFFER_SIZE);
		line = ft_strjoin(str, line_parsing(whatever, fd));
	}
	free(whatever);
	return (line);
}

char	*parse_file(int fd)
{
	char	*str;
	char	*line;

	str = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (str == 0)
	{
		return (0);
	}
	if (!(read(fd, str, BUFFER_SIZE)))
	{
		write(1, "c", 1);
		free(str);
		return (NULL);
	}
	line = line_parsing(str, fd);
	free(str);
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;
	int		i;

	i = BUFFER_SIZE;
	if (fd < 0 || i <= 0)
		return (0);
	line = parse_file(fd);
	if (line && line[0] == 0)
	{
		free(line);
		return (0);
	}
	return (line);
}
