#include "libft.h"

int	ft_find_bn(const char *s)
{
	int	i;

	if (!*s)
		return (-1);
	if (*s == '\n')
		return (0);
	i = ft_find_bn(s + 1);
	if (i == -1)
		return (-1);
	return (i + 1);
}

int	ft_strcpy_until_bn(const char *s, char *result)
{
	if (!*s || *s == '\n')
		return (0);
	*result = *s;
	return (ft_strcpy_until_bn(s + 1, result + 1) + 1);
}

static char	*ft_strjoin_until_bn(char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*result;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	result = malloc(sizeof(char) * (1 + ft_strlen(s1) + ft_strlen(s2)));
	result[0] = 0;
	if (!result)
		return (NULL);
	i = ft_strcpy_until_bn(s1, result);
	j = ft_strcpy_until_bn(s2, result + i);
	if (s2[j] == '\n')
	{
		result[i + j] = '\n';
		i += 1;
	}
	result[i + j] = '\0';
	free(s1);
	return (result);
}

static char	*ft_read_until_bn(int fd, char *buf, char *s, char **rest)
{
	int			r;
	int			end;

	r = 1;
	r = read(fd, buf, BUFFER_SIZE);
	if (r == 0 && *rest)
		free(*rest);
	if (r == 0)
		*rest = NULL;
	if (r == -1 || r == 0)
		return (s);
	buf[r] = 0;
	s = ft_strjoin_until_bn(s, buf);
	end = ft_find_bn(buf);
	if (end != -1)
	{
		if (*rest)
			free(*rest);
		*rest = ft_strdup(buf + end + 1);
		return (s);
	}
	if (r == 0)
		return (s);
	else
		return (ft_read_until_bn(fd, buf, s, rest));
}

int	get_line_from_rest(char **rest, char **s, char **buf)
{
	int		end;
	char	*tmp;

	end = ft_find_bn(*rest);
	*s = ft_strjoin_until_bn(*s, *rest);
	if (end != -1)
	{
		tmp = *rest;
		*rest = ft_strdup(*rest + end + 1);
		free(tmp);
		free(*buf);
	}
	return (end);
}

static char	*get_line(char **rest, char *buf, int fd)
{
	char	*s;
	int		end;

	s = ft_calloc(1, 1);
	if (!s)
	{
		free(buf);
		free(s);
		return (NULL);
	}
	if (*rest)
	{
		end = get_line_from_rest(rest, &s, &buf);
		if (end != -1)
			return (s);
	}
	s = ft_read_until_bn(fd, buf, s, rest);
	free(buf);
	if (!s || !*s)
	{
		free(s);
		return (NULL);
	}
	return (s);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*rest[1024];

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1 * sizeof(char));
	buf[0] = 0;
	if (!buf)
		return (NULL);
	return (get_line(&(rest[fd]), buf, fd));
}
