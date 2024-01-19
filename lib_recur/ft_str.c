#include "libft.h"

int	min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

int	max(size_t a, size_t b)
{
	if (a > b)
		return (a);
	return (b);
}

size_t	ft_strlen(const char *s)
{
	if (!*s)
		return (0);
	return (1 + ft_strlen(s + 1));
}

char	*ft_strchr(const char *s, int c)
{
	if (*s == (unsigned char)c)
		return ((char *)(s));
	if (!*s)
		return (0);
	return (ft_strchr(s + 1, c));
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*result;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	result = ft_calloc(sizeof(char), (i + 1));
	if (!result)
		return (NULL);
	ft_memmove(result, s, i);
	return (result);
}

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	static size_t	i = 0;

	if (!s || !f || !*s)
	{
		i = 0;
		return ;
	}
	f(i, s);
	i += 1;
	ft_striteri(s + 1, f);
}

int	ft_strcpy(const char *s, char *result)
{
	if (!*s)
	{
		*result = 0;
		return (0);
	}
	*result = *s;
	return (ft_strcpy(s + 1, result + 1) + 1);
}

char	*ft_strjoin(char const *s1, char const *s2)
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
	i = ft_strcpy(s1, result);
	j = ft_strcpy(s2, result + i);
	result[i + j] = '\0';
	return (result);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;

	len_src = ft_strlen(src);
	if (size == 0)
		return (len_src);
	len_dst = ft_strlen(dst);
	if (size <= len_dst)
		return (size + len_src);
	ft_memmove(dst + len_dst, src, min(size - len_dst - 1, ft_strlen(src)));
	dst[len_src + len_dst] = '\0';
	return (len_dst + len_src);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	if (!*src || size == 1)
		*(dst) = '\0';
	if (size > 1 && *src)
	{
		*dst = *src;
		ft_strlcpy(dst + 1, src + 1, size - 1);
	}
	return (ft_strlen(src));
}

void ft_strmapi_annexe(char const *s, char *res, char (*f)(unsigned int, char))
{
	static int i = 0;

	if (!*s)
	{
		i = 0;
		return ;
	}
	*res = f(i, *s);
	i += 1;
	ft_strmapi_annexe(s + 1, res + 1, f);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*result;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	result = ft_calloc(sizeof(char), (len + 1));
	if (!result)
		return (NULL);
	ft_strmapi_annexe(s, result, f);
	return (result);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (0 == n)
		return (0);
	if (*s1 && *s2 && *s1 == *s2)
		return (ft_strncmp(s1 + 1, s2 + 1, n - 1));
	return ((*s1) - (*s2));
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	if (len == 0 || !big)
		return (NULL);
	if (*little == '\0' || little == big)
		return ((char *)big);
	if (!ft_strncmp(little, big, min(ft_strlen(little), ft_strlen(big))))
		return ((char *)(big));
	return (ft_strnstr(big + 1, little, len - 1));
}

char	*ft_strrchr_annexe(const char *s, int c, int i)
{
	if (i < 0)
		return (0);
	if (s[i] == (unsigned char)c)
		return ((char *)(s + i));
	return (ft_strrchr_annexe(s, c, i - 1));
}

char	*ft_strrchr(const char *s, int c)
{
	return (ft_strrchr_annexe(s, c, ft_strlen(s)));
}