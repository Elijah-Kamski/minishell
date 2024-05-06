#include "libft.h"

static void	ft_type_pf(char str, va_list va, long int *len)
{
	if (str == '%')
		ft_printchar_pf(str, len);
	else if (str == 'c')
		ft_printchar_pf(va_arg(va, int), len);
	else if (str == 's')
		ft_printstr_pf(va_arg(va, char *), len);
	else if (str == 'd' || str == 'i')
		ft_printnumber_pf(va_arg(va, int), len);
	else if (str == 'x')
		ft_printhex_pf(va_arg(va, unsigned int), 0, len);
	else if (str == 'X')
		ft_printhex_pf(va_arg(va, unsigned int), 1, len);
	else if (str == 'u')
		ft_printnumber_pf(va_arg(va, unsigned int), len);
	else if (str == 'p')
		ft_printptr_pf(va_arg(va, unsigned long int), len);
}

int	ft_printf(const char *str, ...)
{
	long int		len;
	va_list			va;
	unsigned int	i;

	len = 0;
	i = 0;
	va_start(va, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			ft_type_pf(str[++i], va, &len);
		}
		else
			ft_printchar_pf(str[i], &len);
		i++;
	}
	va_end(va);
	return (len);
}
