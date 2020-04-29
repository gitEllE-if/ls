#include "libft.h"

void		*ft_memset(void *b, int c, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = (char *)b;
	while (i < len)
		dest[i++] = (unsigned char)c;
	return (b);
}
