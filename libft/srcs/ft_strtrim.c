#include "libft.h"

static int	is_whitespaces(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char		*ft_strtrim(char const *s1)
{
	unsigned int	i;
	char			*str_trim;
	char			*s;

	s = (char*)s1;
	if (!s)
		return (NULL);
	i = 0;
	while (is_whitespaces(*s) && *s)
		s++;
	if ((i = ft_strlen(s)) > 0)
	{
		i--;
		while (is_whitespaces(s[i]))
			i--;
	}
	if (!(str_trim = (char *)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	ft_strncpy(str_trim, s, i + 2);
	str_trim[i + 1] = '\0';
	return (str_trim);
}
