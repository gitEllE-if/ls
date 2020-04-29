#include "libft.h"

void	switch_job(void **array, int idx, int *force_stop)
{
	void	*tmp;

	tmp = array[idx + 1];
	array[idx + 1] = array[idx];
	array[idx] = tmp;
	force_stop = 0;
}

int		back_bubble_sort(void **array, int size,
		int (*to_switch)(void *cur, void *back))
{
	int		idx;
	int		force_stop;
	int		bot_lim;
	int		run;

	run = 0;
	if (size < 2)
		return (run);
	bot_lim = -1;
	while (bot_lim < size - 2)
	{
		run += 1;
		idx = size - 1;
		force_stop = 1;
		while (--idx > bot_lim)
		{
			if (to_switch(array[idx + 1], array[idx]))
				switch_job(array, idx, &force_stop);
		}
		if (force_stop)
			break ;
		bot_lim += 1;
	}
	return (run);
}
