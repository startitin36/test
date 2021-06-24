#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;
	
	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	const unsigned char	*ptr_src;
	unsigned char		*ptr_dest;

	ptr_dest = dest;
	ptr_src = src;
	if (dest == src)
		return (dest);
	if (dest > src)
	{
		while (len--)
			*(ptr_dest + len) = *(ptr_src + len);
		return (dest);
	}
	while (len--)
		*ptr_dest++ = *ptr_src++;
	return (dest);
}

int	has_new_line(const char *str)
{
	int	i;
	
	i = 0;
	if (!str)
		return(0);
	while (str[i])
	{
		if ((str[i]) == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*joined;

	if (!s1 && !s2)
		return (0);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	joined = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!joined)
		return (0);
	ft_memmove(joined, s1, 	s1_len);
	ft_memmove(joined + s1_len, s2, s2_len);
	joined[s1_len + s2_len] = '\0';
	free((char *)s1);
	return (joined);
}
