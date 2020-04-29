#include "ft_ls.h"

int32_t	mtimecmp(t_ftree *a, t_ftree *b)
{
	if (a->st->st_mtime == b->st->st_mtime)
		return (b->st->st_mtimespec.tv_nsec - a->st->st_mtimespec.tv_nsec);
	else
		return (b->st->st_mtime - a->st->st_mtime);
}

int32_t	revmtimecmp(t_ftree *a, t_ftree *b)
{
	if (a->st->st_mtime == b->st->st_mtime)
		return (a->st->st_mtimespec.tv_nsec - b->st->st_mtimespec.tv_nsec);
	else
		return (a->st->st_mtime - b->st->st_mtime);
}

int32_t	btimecmp(t_ftree *a, t_ftree *b)
{
	if (a->st->st_birthtime == b->st->st_birthtime)
		return (b->st->st_birthtimespec.tv_nsec -
											a->st->st_birthtimespec.tv_nsec);
	else
		return (b->st->st_birthtime - a->st->st_birthtime);
}

int32_t	revbtimecmp(t_ftree *a, t_ftree *b)
{
	if (a->st->st_birthtime == b->st->st_birthtime)
		return (a->st->st_birthtimespec.tv_nsec -
											b->st->st_birthtimespec.tv_nsec);
	else
		return (a->st->st_birthtime - b->st->st_birthtime);
}
