#include "libft.h"

//This function removes the first line of text from the buffer
//and shifts the remaining content to the beginning
//of the buffer. The remainder of the buffer is then null-terminated.
void	remove_first_line_from_buffer(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	while (buffer[i] && buffer[++i])
		buffer[j++] = buffer[i];
	while (buffer[j])
		buffer[j++] = '\0';
}

//This function uses null terminators ('\0') to remove
//everyting after the first newline character ('\n') in next_line
//It also shifts the buffer to the left,
//removing everything before the newline character ('\n')
//and null terminating the rest ('\0')
void	adjust_line_and_buffer(char *next_line, char *buffer)
{
	int	i;

	i = 0;
	while (next_line[i] && next_line[i] != '\n')
		i++;
	while (next_line[i] && next_line[++i])
		next_line[i] = '\0';
	remove_first_line_from_buffer(buffer);
}

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][GNL_BUFFER_SIZE + 1];
	int			characters_read;
	char		*next_line;

	characters_read = 1;
	if (GNL_BUFFER_SIZE <= 0 || fd < 0 || fd >= FOPEN_MAX)
	{
		if (fd < FOPEN_MAX && fd >= 0)
			ft_bzero_gnl(buffer[fd], GNL_BUFFER_SIZE);
		return (NULL);
	}
	next_line = ft_strjoin_gnl(NULL, buffer[fd]);
	while (!(ft_strchr_gnl(next_line, '\n')) && characters_read > 0)
	{
		ft_bzero_gnl(buffer[fd], GNL_BUFFER_SIZE);
		characters_read = read(fd, buffer[fd], GNL_BUFFER_SIZE);
		next_line = ft_strjoin_gnl(next_line, buffer[fd]);
	}
	adjust_line_and_buffer(next_line, buffer[fd]);
	if (!next_line || !next_line[0] || characters_read < 0)
	{
		free(next_line);
		return (NULL);
	}
	return (next_line);
}
