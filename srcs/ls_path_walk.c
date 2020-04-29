#include "ft_ls.h"

static char		*g_fullpath;
static t_ftree	**g_ft;

void				ft_ftwalk(char *pathname, t_ftree **ft)
{
	uint64_t	hash;

	g_fullpath = (char *)malloc(sizeof(char) * PATH_MAX);
	ft_strcpy(g_fullpath, pathname);
	hash = ft_hash(g_fullpath);
	g_ft = ft;
	ft_recursive_walk(NULL, 0, hash);
	free(g_fullpath);
}

static inline DIR	*ft_rec_walk(struct dirent *dirp, uint64_t *hash, int *n,
															t_ftree **new_elem)
{
	DIR	*dp;

	if (dirp != NULL)
	{
		if (dirp->d_type != 4 ||
			(dirp->d_name[0] == '.' && !(g_lsf & (F_SEEDOT | F_LISTDOT))))
			return (NULL);
		else
			*hash = ft_hash(g_fullpath);
	}
	if (g_lsf & F_LISTDIR)
		return (NULL);
	*n = ft_strlen(g_fullpath);
	if (g_fullpath[*n - 1] != '/')
	{
		g_fullpath[(*n)++] = '/';
		g_fullpath[*n] = 0;
	}
	if ((dp = opendir(g_fullpath)) == NULL)
	{
		(*new_elem)->err = errno == 20 ? 0 : errno;
		return (NULL);
	}
	return (dp);
}

void				ft_recursive_walk(struct dirent *dirp, uint32_t lev,
																uint64_t hash)
{
	DIR				*dp;
	int				n;
	t_ftree			*new_elem;

	new_elem = ft_ftree_fill(g_fullpath, dirp, lev, hash);
	if ((dp = ft_rec_walk(dirp, &hash, &n, &new_elem)) == NULL)
		return ;
	if (++lev == 2 && !(g_lsf & F_RECURSIVE))
	{
		closedir(dp);
		return ;
	}
	while ((dirp = readdir(dp)) != NULL)
	{
		if (!ft_strcmp(dirp->d_name, ".") || !ft_strcmp(dirp->d_name, ".."))
		{
			if ((g_lsf & (F_LISTDOT | F_SEEDOT)) == F_SEEDOT)
				ft_ftree_fill(ft_strcat(g_fullpath, "."), dirp, lev, hash);
			continue;
		}
		ft_strcpy(&g_fullpath[n], dirp->d_name);
		ft_recursive_walk(dirp, lev, hash);
	}
	g_fullpath[n - 1] = 0;
	closedir(dp);
}

t_ftree				*ft_ftree_fill(char *fullname, struct dirent *dirp,
													uint32_t lev, uint64_t hash)
{
	t_ftree		*elem;
	t_ftree		*new_elem;

	elem = *g_ft;
	if ((new_elem = ft_ftree_new_elem(fullname, lev, dirp, hash)) && !*g_ft)
	{
		*g_ft = new_elem;
		(*g_ft)->last = new_elem;
	}
	else
	{
		while (elem->down && elem->lev < lev)
			elem = elem->down;
		if (elem->lev == lev)
		{
			elem->last->next = new_elem;
			elem->last = new_elem;
		}
		if (elem->lev < lev)
		{
			elem->down = new_elem;
			elem->down->last = new_elem;
		}
	}
	return (new_elem);
}
