#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	i;
	size_t	src_len;

	dest_len = 0;
	i = 0;
	src_len = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (dest_len + 1 > size)
		return (size + src_len);
	while (src[i] && i < size - dest_len - 1)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
