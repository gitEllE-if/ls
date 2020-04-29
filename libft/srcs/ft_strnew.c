#include "libft.h"

char	*ft_strnew(size_t size)
{
	char		*str;
	long int	max;

	max = -1;
	max = (unsigned long)max >> 1;
	if (size == (unsigned long)max)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}
