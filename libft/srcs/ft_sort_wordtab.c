#include "libft.h"

void	ft_sort_wordtab(char **tab)
{
	int	swapped;
	int	i;

	i = 1;
	swapped = 1;
	if (!tab)
		return ;
	if (!*tab)
		return ;
	while (swapped)
	{
		i = 1;
		swapped = 0;
		while (tab[i])
		{
			if (ft_strcmp(tab[i - 1], tab[i]) > 0)
			{
				ft_swap(&tab[i - 1], &tab[i]);
				swapped = 1;
			}
			i++;
		}
	}
}
