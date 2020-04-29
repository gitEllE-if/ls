#include "ft_ls.h"

int32_t	atimecmp(t_ftree *a, t_ftree *b)
{
	if (a->st->st_atime == b->st->st_atime)
		return (b->st->st_atimespec.tv_nsec - a->st->st_atimespec.tv_nsec);
	else
		return (b->st->st_atime - a->st->st_atime);
}

int32_t	revatimecmp(t_ftree *a, t_ftree *b)
{
	if (a->st->st_atime == b->st->st_atime)
		return (a->st->st_atimespec.tv_nsec - b->st->st_atimespec.tv_nsec);
	else
		return (a->st->st_atime - b->st->st_atime);
}

int32_t	ctimecmp(t_ftree *a, t_ftree *b)
{
	if (a->st->st_ctime == b->st->st_ctime)
		return (b->st->st_ctimespec.tv_nsec - a->st->st_ctimespec.tv_nsec);
	else
		return (b->st->st_ctime - a->st->st_ctime);
}

int32_t	revctimecmp(t_ftree *a, t_ftree *b)
{
	if (a->st->st_ctime == b->st->st_ctime)
		return (a->st->st_ctimespec.tv_nsec - b->st->st_ctimespec.tv_nsec);
	else
		return (a->st->st_ctime - b->st->st_ctime);
}
