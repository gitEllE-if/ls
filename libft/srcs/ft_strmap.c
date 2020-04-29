#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str_map;
	size_t	i;

	if (!s || !f)
		return (NULL);
	if (!(str_map = ft_strnew(ft_strlen(s))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		str_map[i] = f(s[i]);
		i++;
	}
	return (str_map);
}
