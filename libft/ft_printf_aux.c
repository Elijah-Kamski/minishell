#include "libft.h"

void	ft_printchar_pf(char c, long int *len)
{
	write(1, &c, 1);
	(*len)++;
}

void	ft_printstr_pf(char *s, long int *len)
{
	if (!s)
		s = "(null)";
	while (*s)
	{
		ft_printchar_pf(*s, len);
		s++;
	}
}

void	ft_printnumber_pf(long int n, long int *len)
{
	if (n < 0)
	{
		ft_printchar_pf('-', len);
		n = -n;
	}
	if (n >= 10)
		ft_printnumber_pf(n / 10, len);
	ft_printchar_pf(n % 10 + '0', len);
}

void	ft_printhex_pf(unsigned int n, int is_upper, long int *len)
{
	char	*hex_chars;

	if (is_upper)
		hex_chars = HEX_UPP;
	else
		hex_chars = HEX_LOW;
	if (n >= 16)
		ft_printhex_pf(n / 16, is_upper, len);
	ft_printchar_pf(hex_chars[n % 16], len);
}

void	ft_printptr_pf(unsigned long int ptr, long int *len)
{
	if (!ptr)
	{
		ft_printstr_pf("(nil)", len);
		return ;
	}
	if (ptr < 16)
	{
		ft_printstr_pf("0x", len);
		ft_printchar_pf(HEX_LOW[ptr % 16], len);
		return ;
	}
	ft_printptr_pf(ptr / 16, len);
	ft_printchar_pf(HEX_LOW[ptr % 16], len);
}
