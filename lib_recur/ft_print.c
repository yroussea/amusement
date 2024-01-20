#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
		ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

size_t	ft_putlchar(int c)
{
	write(1, &c, 1);
	return (1);
}

static size_t	ft_putlchar_hexa_low(int c)
{
	if (c < 10)
		return (ft_putlchar(c + '0'));
	return (ft_putlchar('a' + c - 10));
}

static size_t	ft_putlchar_hexa_up(int c)
{
	if (c < 10)
		return (ft_putlchar(c + '0'));
	return (ft_putlchar('A' + c - 10));
}

size_t	ft_putlhexa_low(unsigned long int nb)
{
	if (nb >= 16)
		return (ft_putlhexa_low(nb / 16) + ft_putlchar_hexa_low(nb % 16));
	return (ft_putlchar_hexa_low(nb));
}

size_t	ft_putlhexa_up(unsigned long int nb)
{
	if (nb >= 16)
		return (ft_putlhexa_up(nb / 16) + ft_putlchar_hexa_up(nb % 16));
	return (ft_putlchar_hexa_up(nb));
}

size_t	ft_putlnbr(int n)
{
	if (n == -2147483648)
		return (ft_putlstr("-2147483648"));
	if (n < 0)
		return (ft_putlchar('-') + ft_putlnbr(n * -1));
	if (n < 10)
		return (ft_putlchar(n + '0'));
	return (ft_putlnbr(n / 10) + ft_putlchar(n % 10 + '0'));
}

size_t	ft_putlunbr(unsigned int n)
{
	if (n < 10)
		return (ft_putlchar(n + '0'));
	return (ft_putlnbr(n / 10) + ft_putlchar(n % 10 + '0'));
}

size_t	ft_putlpoint(void *p)
{
	if (p == 0)
		return (ft_putlstr("(nil)"));
	return (ft_putlstr("0x") + ft_putlhexa_low((unsigned long long)p));
}

size_t	ft_putlstr(char *s)
{
	if (!s)
		return (write(1, "(null)", 6));
	if (!*s)
		return (0);
	return (ft_putlchar(*s) + ft_putlstr(s + 1));
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(n * -1, fd);
	}
	else if (n < 10)
	{
		ft_putchar_fd(n + '0', fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
}

size_t	ft_putmultstr(char **strs)
{
	if (!strs || !*strs)
		return (0);
	return (ft_printf("%s\n", *strs) + ft_putmultstr(strs + 1));
}

size_t	ft_put_stack(t_stack *stack)
{
	if (!stack)
		return (0);
	return (ft_printf("%d ", stack->content) + ft_put_stack(stack->next));
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

static size_t	ft_format(const char *c, va_list args)
{
	if (*c == 'S')
		return (ft_putmultstr(va_arg(args, char **)));
	if (*c == 'c')
		return (ft_putlchar(va_arg(args, int)));
	if (*c == 's')
		return (ft_putlstr(va_arg(args, char *)));
	if (*c == 'u')
		return (ft_putlunbr(va_arg(args, unsigned int)));
	if (*c == 'd' || *c == 'i')
		return (ft_putlnbr(va_arg(args, int)));
	if (*c == '%')
		return (ft_putlchar('%'));
	if (*c == 'x')
		return (ft_putlhexa_low(va_arg(args, unsigned int)));
	if (*c == 'X')
		return (ft_putlhexa_up(va_arg(args, unsigned int)));
	if (*c == 'p')
		return (ft_putlpoint(va_arg(args, void *)));
	if (*c == '\0')
		return (-1);
	return (ft_putlchar('%') + ft_putlchar(*c));
}

static int	ft_put_percent(const char *c, va_list args, int *boole)
{
	int	len;

	len = ft_format(c, args);
	if (len == -1)
		*boole = 1;
	return (len);
}

int	printf_annex(const char *str, va_list args, int *boole)
{
	if (*boole == 1 || !str || !*str)
		return (0);
	if (*str == '%')
		return (ft_put_percent(str + 1, args, boole) + \
			printf_annex(str + 2, args, boole));
	else
		return (ft_putlchar(*str) + printf_annex(str + 1, args, boole));
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		boole;

	boole = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	len = printf_annex(str, args, &boole);
	va_end(args);
	if (boole)
		return (-1);
	return (len);
}
