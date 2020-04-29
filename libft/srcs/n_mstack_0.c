#include "n_mstack.h"

t_list	**get_mstack(void)
{
	static t_list	*mstack;

	return (&mstack);
}

int		add_mstack(void *to_add)
{
	t_list	*add;

	if (!to_add)
	{
		free_all_mstack();
		return (1);
	}
	add = ft_lstnew(NULL, 0);
	if (!add)
	{
		free(to_add);
		free_all_mstack();
		return (1);
	}
	add->content = to_add;
	ft_lstadd(get_mstack(), add);
	return (0);
}

int		num_mstack(void)
{
	t_list	*mstack;
	int		out;

	out = 0;
	mstack = *(get_mstack());
	while (mstack)
	{
		++out;
		mstack = mstack->next;
	}
	return (out);
}
