#include "ft_ls.h"

static inline void	ft_free_inside(t_ftree **elem)
{
	if ((*elem)->st)
		free((*elem)->st);
	if ((*elem)->ugf)
		free((*elem)->ugf);
	free(*elem);
}

void				ft_ftree_free(t_ftree **ft, int8_t dir)
{
	t_ftree	*elem;
	t_ftree *clear1;
	t_ftree *clear2;

	if (!*ft)
		return ;
	elem = *ft;
	if (dir)
		elem = elem->down;
	while (elem)
	{
		clear1 = elem->down;
		while (elem)
		{
			clear2 = elem->next;
			ft_free_inside(&elem);
			elem = clear2;
		}
		elem = clear1;
	}
	if (dir)
		ft_free_inside(ft);
	*ft = NULL;
}
