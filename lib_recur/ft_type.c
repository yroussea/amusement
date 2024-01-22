#include "libft.h"

int	ft_atoi_anx(const char *s, int nb)
{
	if (!s || !*s)
		return (nb);
	if (ft_isdigit(*s))
		return (ft_atoi_anx(s + 1, (*s - '0') + nb * 10));
	return (nb);
}

int	ft_atoi(const char *s)
{
	if (*s == ' ' || (9 <= *s && *s <= 13))
		return (ft_atoi(s + 1));
	if (*s == '-')
		return (-1 * ft_atoi_anx(s + 1, 0));
	if (*s == '+')
		return (ft_atoi_anx(s + 1, 0));
	return (ft_atoi_anx(s, 0));
}

static size_t	len_number(long int n)
{
	if (n > 9)
		return (1 + len_number(n / 10));
	return (1);
}

void	fill_itao(char *result, size_t len, int n)
{
	if (len == 0)
		return ;
	result[len - 1] = n % 10 + '0';
	fill_itao(result, len - 1, n / 10);
}

void	fill_neg_itao(char *result, size_t len, long int n)
{
	if (len == 0)
		return ;
	result[len - 1] = n % 10 + '0';
	fill_itao(result, len - 1, n / 10);
}

static char	*ft_neg_number(long int nb)
{
	size_t	len;
	char	*result;

	len = len_number(nb);
	result = ft_calloc(sizeof(char), (len + 2));
	if (!result)
		return (NULL);
	result[0] = '-';
	fill_neg_itao(result + 1, len, nb);
	return (result);
}

char	*ft_itoa(int n)
{
	char		*result;
	size_t		len;

	if (n >= 0)
	{
		len = len_number(n);
		result = ft_calloc(sizeof(char), (len + 1));
		if (!result)
			return (NULL);
		fill_itao(result, len, n);
	}
	else
		result = ft_neg_number((long int)n * -1);
	return (result);
}
