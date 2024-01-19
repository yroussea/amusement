#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	if (n == 0)
		return ;
	*(unsigned char *)(s) = (unsigned char) '\0';
	ft_bzero(s + 1, n - 1);
}

void	*ft_calloc(size_t nmeb, size_t size)
{
	char	*array;

	if (size == 0 || nmeb == 0)
		return (malloc(1));
	if ((long long)size < 0 || (long long)nmeb < 0)
		return (NULL);
	array = malloc(size * nmeb);
	if (!array)
		return (NULL);
	ft_bzero(array, size * nmeb);
	return (array);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	if (n == 0)
		return (NULL);
	if (*(unsigned char *)(s) == (unsigned char)c)
		return ((void *)(s));
	return (ft_memchr(s + 1, c, n - 1));
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (!s1 && !s2)
		return (0);
	if (n == 0)
		return (0);
	if (*(unsigned char *)(s1) != *(unsigned char *)(s2))
		return (*(unsigned char *)(s1) - *(unsigned char *)(s2));
	return (ft_memcmp(s1 + 1, s2 + 1, n - 1));
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (NULL);
	if (n == 0)
		return (dest);
	*(unsigned char *)(dest) = *(unsigned char *)(src);
	ft_memcpy(dest + 1, src + 1, n - 1);
	return (dest);
}

void	*ft_memcpy_from_back(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (NULL);
	if (n == 0)
		return (dest);
	ft_memcpy_from_back(dest + 1, src + 1, n - 1);
	*(unsigned char *)(dest) = *(unsigned char *)(src);
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (dest);
	if (dest > src)
		ft_memcpy_from_back(dest, src, n);
	else
		ft_memcpy(dest, src, n);
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	if (n == 0)
		return (NULL);
	*(unsigned char *)(s) = (unsigned char)c;
	ft_memset(s + 1, c, n - 1);
	return (s);
}
