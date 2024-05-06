#include "libft.h"

//This function sets the first n bytes of the 
//character array s to null ('\0').
//If s is an empty string or n is 0, it returns NULL.
void	*ft_bzero_gnl(char *s, size_t n)
{
	size_t	i;

	if (!s[0])
		return (NULL);
	i = 0;
	while (i < n)
		s[i++] = '\0';
	return (NULL);
}

//This function calculates and returns
//the length (number of characters)
//of the input string s and is terminated
//by a null character ('\0').
int	ft_strlen_gnl(const char *s)
{
	int	i;

	i = 0;
	while ((s[i] != '\0'))
		i++;
	return (i);
}

//This function concatenates two strings s1 and s2
//to create a new dynamically allocated string (newstr).
//It allocates memory to hold both strings,
//copies the contents of s1 and s2 into newstr,
//and returns the result. It also frees the memory allocated for s1.
char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*newstr;
	int		i;
	int		length;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	newstr = (char *) malloc(((ft_strlen_gnl(s1) + ft_strlen_gnl(s2)) + 1)
			* sizeof(char));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	length = -1;
	while (s1[++length])
		newstr[length] = s1[length];
	while (s2[i])
		newstr[length++] = s2[i++];
	free(s1);
	newstr[length] = '\0';
	return (newstr);
}

//This function searches for the character c in the string s.
//If c is found in s, it returns 1; otherwise, it returns 0.
int	ft_strchr_gnl(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s[0])
		return (0);
	while (s[i])
	{
		if ((char)c == s[i])
			return (1);
		i++;
	}
	if ((char)c == s[i])
		return (1);
	else
		return (0);
}
