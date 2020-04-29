#include "libft.h"

void	bubble_sort(void **array, int size, int (*f)(void *input))
{
	int		idx;
	int		before;
	int		new_val;
	void	*tmp;

	if (size < 2)
		return ;
	while (size > 1)
	{
		before = f(array[0]);
		idx = 0;
		while (++idx < size)
		{
			new_val = f(array[idx]);
			if (before <= new_val)
				before = new_val;
			else
			{
				tmp = array[idx];
				array[idx] = array[idx - 1];
				array[idx - 1] = tmp;
			}
		}
		size -= 1;
	}
}
