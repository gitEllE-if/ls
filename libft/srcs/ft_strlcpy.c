#include "libft.h"

size_t		ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if (!src)
		return (0);
	i = 0;
	j = 0;
	while (src[i])
		i++;
	if (!dest || size == 0)
		return (i);
	while (j < size - 1 && src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = '\0';
	return (i);
}
