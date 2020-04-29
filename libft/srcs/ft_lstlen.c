#include "libft.h"

static size_t	ft_lstlen_rec(t_list *lst, size_t count)
{
	if (!lst)
		return (count);
	return (ft_lstlen_rec(lst->next, count + 1));
}

size_t			ft_lstlen(t_list *lst)
{
	if (!lst)
		return (0);
	return (ft_lstlen_rec(lst->next, 1));
}
