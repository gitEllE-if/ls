#include "ft_ls.h"

static void			ft_smode_type(int mode, char **type)
{
	if (S_ISDIR(mode))
		*(*type)++ = 'd';
	else if (S_ISCHR(mode))
		*(*type)++ = 'c';
	else if (S_ISBLK(mode))
		*(*type)++ = 'b';
	else if (S_ISREG(mode))
		*(*type)++ = '-';
	else if (S_ISLNK(mode))
		*(*type)++ = 'l';
	else if (S_ISSOCK(mode))
		*(*type)++ = 's';
	else if (S_ISFIFO(mode))
		*(*type)++ = 'p';
	else
		*(*type)++ = '?';
}

static void			ft_smode_usr(int mode, char **usr)
{
	int	md;

	*(*usr)++ = (mode & S_IRUSR) ? 'r' : '-';
	*(*usr)++ = (mode & S_IWUSR) ? 'w' : '-';
	if ((md = mode & (S_IXUSR | S_ISUID)) == 0)
		*(*usr)++ = '-';
	else if (md == S_IXUSR)
		*(*usr)++ = 'x';
	else if (md == S_ISUID)
		*(*usr)++ = 'S';
	else if (md == (S_IXUSR | S_ISUID))
		*(*usr)++ = 's';
}

static void			ft_smode_grp(int mode, char **grp)
{
	int md;

	*(*grp)++ = (mode & S_IRGRP) ? 'r' : '-';
	*(*grp)++ = (mode & S_IWGRP) ? 'w' : '-';
	if ((md = mode & (S_IXGRP | S_ISGID)) == 0)
		*(*grp)++ = '-';
	else if (md == S_IXGRP)
		*(*grp)++ = 'x';
	else if (md == S_ISGID)
		*(*grp)++ = 'S';
	else if (md == (S_IXGRP | S_ISGID))
		*(*grp)++ = 's';
}

static inline void	ft_smode_oth(int mode, char **oth)
{
	int	md;

	*(*oth)++ = (mode & S_IROTH) ? 'r' : '-';
	*(*oth)++ = (mode & S_IWOTH) ? 'w' : '-';
	if ((md = mode & (S_IXOTH | S_ISVTX)) == 0)
		*(*oth)++ = '-';
	else if (md == S_IXOTH)
		*(*oth)++ = 'x';
	else if (md == S_ISVTX)
		*(*oth)++ = 'T';
	else if (md == (S_IXOTH | S_ISVTX))
		*(*oth)++ = 't';
}

void				ft_strmode(int mode, char *str)
{
	ft_smode_type(mode, &str);
	ft_smode_usr(mode, &str);
	ft_smode_grp(mode, &str);
	ft_smode_oth(mode, &str);
	*str++ = ' ';
	*str = '\0';
}
