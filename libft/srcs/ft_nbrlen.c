#include "libft.h"

size_t	ft_nbrlen(int nbr)
{
	size_t	out;

	out = 1;
	while ((nbr /= 10) != 0)
		out += 1;
	if (nbr < 0)
		out += 1;
	return (out);
}
