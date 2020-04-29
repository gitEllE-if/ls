#include "ft_ls.h"

void				ft_ftree_push_back(t_ftree **ft, t_ftree *node)
{
	t_ftree *elem;

	elem = *ft;
	node->parent = 0;
	if (!*ft)
		*ft = node;
	else
	{
		while (elem->next)
			elem = elem->next;
		elem->next = node;
	}
}

t_ftree				*ft_ftree_new_elem(char *fullname, uint32_t lev,
											struct dirent *dirp, uint64_t hash)
{
	t_ftree		*elem;
	struct stat *status;
	int32_t		ret;

	elem = (t_ftree*)malloc(sizeof(t_ftree));
	status = (struct stat *)malloc(sizeof(struct stat));
	elem->lev = lev;
	elem->root = 0;
	elem->parent = hash;
	ft_strcpy(elem->fullname, fullname);
	dirp ? ft_strcpy(elem->name, dirp->d_name) :
										ft_strcpy(elem->name, elem->fullname);
	elem->next = NULL;
	elem->down = NULL;
	elem->ugf = NULL;
	ret = g_lsf & F_GOLINK ? stat(fullname, status) : lstat(fullname, status);
	elem->err = ret != 0 ? errno : 0;
	elem->st = status;
	elem->dot = dirp && (ft_strcmp(dirp->d_name, ".") == 0 ||
									ft_strcmp(dirp->d_name, "..") == 0) ? 1 : 0;
	elem->hidn = dirp && dirp->d_name[0] == '.' ? 1 : 0;
	return (elem);
}

static inline void	ft_swap_ptr(t_ftree **ft, t_ftree **elem,
										t_ftree **elem_prev, int32_t *swapped)
{
	if (*elem == *ft)
	{
		*ft = (*elem)->next;
		(*elem)->next = (*ft)->next;
		(*ft)->next = *elem;
		*elem_prev = *ft;
		*elem = *ft;
	}
	else
	{
		(*elem_prev)->next = (*elem)->next;
		(*elem)->next = (*elem_prev)->next->next;
		(*elem_prev)->next->next = *elem;
		*elem = *elem_prev;
	}
	*swapped = 1;
}

void				ft_ftree_sort(t_ftree **ft, t_ftree *down,
										int32_t (*ft_cmp)(t_ftree *, t_ftree *))
{
	int32_t	swapped;
	t_ftree	*elem;
	t_ftree	*elem_prev;

	if (down)
		(*ft)->down = NULL;
	swapped = 1;
	while (swapped)
	{
		elem_prev = *ft;
		elem = *ft;
		swapped = 0;
		while (elem && elem->next)
		{
			if (elem->parent == elem->next->parent &&
												ft_cmp(elem, elem->next) > 0)
				ft_swap_ptr(ft, &elem, &elem_prev, &swapped);
			else if (elem != *ft)
				elem_prev = elem_prev->next;
			elem = elem->next;
		}
	}
	if (down)
		(*ft)->down = down;
}

void				ft_ftree_downsort(t_ftree **ft,
										int32_t (*ft_cmp)(t_ftree *, t_ftree *))
{
	t_ftree	*elem;
	t_ftree *elem_prev;

	elem = *ft;
	elem_prev = *ft;
	if (!*ft || (!(*ft)->down && !(*ft)->next))
		return ;
	while (elem)
	{
		ft_ftree_sort(&elem, elem->down, ft_cmp);
		if (elem != *ft)
			elem_prev->down = elem;
		elem_prev = elem;
		elem = elem->down;
	}
}
