#include "libft.h"

int    ft_atoi_anx(const char *s, int nb)
{
	if (!s || !*s)
		return (nb);
	if (ft_isdigit(*s))
		return (ft_atoi_anx(s + 1, (*s - '0') + nb * 10));
	return (nb);
}

int    ft_atoi(const char *s)
{
	if (*s == ' ' || (9 <= *s && *s <= 13))
		return (ft_atoi(s + 1));
	if (*s == '-')
		return (-1 * ft_atoi_anx(s + 1, 0));
	if (*s == '+')
		return (ft_atoi_anx(s + 1, 0));
	return (ft_atoi_anx(s, 0));
}