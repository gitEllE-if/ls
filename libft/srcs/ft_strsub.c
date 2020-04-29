#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str_sub;
	size_t	i;

	if (!s || !(str_sub = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		str_sub[i] = s[start + i];
		i++;
	}
	return (str_sub);
}
