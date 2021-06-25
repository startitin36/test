#include "get_next_line.h"

char	*fix_remainder(char *str)
{
	char	*rtn;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (!str)
		return (NULL);
	while (str[len] && str[len] != '\n')
		len++;
	if (!str[len])
	{
		free(str);
		return (NULL);
	}
	rtn = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (!rtn)
		return (0);
	while (str[++len])
		rtn[i++] = str[len];
	rtn[i] = '\0';
	free(str);
	return (rtn);
}

static char	*get_new_line(char *str)
{
	int		len;
	char	*new_line;

	len = 0;
	if (!str)
		return (NULL);
	while (str[len] && str[len] != '\n')
		len++;
	new_line = malloc(sizeof(char) * (len + 1));
	if (!new_line)
		return (NULL);
	len = -1;
	while (str[++len] && str[len] != '\n')
		new_line[len] = str[len];
	new_line[len] = '\0';
	return (new_line);
}	

static int	read_and_join(int fd, char **remainder, char *buf)
{
	int	bytes_read;

	bytes_read = 1;
	while (NULL == ft_strchr(*remainder, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (GNL_ERROR);
		buf[bytes_read] = '\0';
		*remainder = ft_strjoin(*remainder, buf);
	}
	return (bytes_read);
}

int	get_next_line(int fd, char **line)
{
	static char	*remainder;
	char		*buf;
	int			bytes_read;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (GNL_ERROR);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (GNL_ERROR);
	bytes_read = read_and_join(fd, &remainder, buf);
	free(buf);
	if (bytes_read == -1)
		return (GNL_ERROR);
	*line = get_new_line(remainder);
	remainder = fix_remainder(remainder);
	if (bytes_read == 0)
		return (GNL_EOF);
	return (GNL_LINEBREAK);
}
