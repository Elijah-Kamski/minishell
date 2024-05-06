#include "libft.h"

static void	ft_converter(char *str, int len, long num)
{
	while (num > 0)
	{
		str[len] = 48 + (num % 10);
		num /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	l;
	int			i;

	l = n;
	i = (ft_numlen(l));
	if (l <= 0)
		i++;
	str = (char *)malloc(i + 1);
	if (str == NULL)
		return (NULL);
	str[i--] = '\0';
	if (l == 0)
	{
		str[0] = 48;
		return (str);
	}
	else if (l < 0)
	{
		str[0] = '-';
		l *= -1;
	}
	ft_converter(str, i, l);
	return (str);
}
