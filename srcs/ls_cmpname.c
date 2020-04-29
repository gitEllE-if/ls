#include "ft_ls.h"

int32_t	namecmp(t_ftree *a, t_ftree *b)
{
	return (ft_strcmp(a->name, b->name));
}

int32_t	revnamecmp(t_ftree *a, t_ftree *b)
{
	return (ft_strcmp(b->name, a->name));
}

int32_t	sizecmp(t_ftree *a, t_ftree *b)
{
	if (b->st->st_size == a->st->st_size)
		return (namecmp(a, b));
	else
		return (b->st->st_size - a->st->st_size);
}

int32_t	revsizecmp(t_ftree *a, t_ftree *b)
{
	if (b->st->st_size == a->st->st_size)
		return (revnamecmp(a, b));
	else
		return (a->st->st_size - b->st->st_size);
}
