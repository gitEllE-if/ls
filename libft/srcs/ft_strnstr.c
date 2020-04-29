#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t n_len;

	if (*needle == '\0')
		return ((char *)haystack);
	n_len = ft_strlen(needle);
	while (*haystack && len >= n_len)
	{
		if (ft_strnequ(haystack, needle, n_len))
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
