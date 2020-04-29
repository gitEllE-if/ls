#include "ft_ls.h"

static void	ft_print_link(t_ftree *ft)
{
	int32_t	len;
	char	name[PATH_MAX];
	char	link[PATH_MAX];

	ft_sprintf(name, "%s", ft->fullname);
	if ((len = readlink(name, link, sizeof(link) - 1)) == -1)
	{
		ft_fprintf(2, "\n%s: %s: %s\n", g_app_name, name, strerror(errno));
		return ;
	}
	link[len] = '\0';
	ft_printf(" -> %s", link);
}

static void	ft_print_time(time_t tm, int32_t i)
{
	char	*str_tm;

	str_tm = ctime(&tm);
	while (i < 11)
		ft_printf("%c", str_tm[i++]);
	if (g_lsf & F_SECTIME)
	{
		i = 11;
		while (i < 24)
			ft_printf("%c", str_tm[i++]);
	}
	else if ((tm + 86400 * (365 / 2)) > time(NULL))
	{
		i = 11;
		while (i < 16)
			ft_printf("%c", str_tm[i++]);
	}
	else
	{
		ft_printf(" ");
		i = 20;
		while (i < 24)
			ft_printf("%c", str_tm[i++]);
	}
	ft_printf(" ");
}

static char	ft_acl_xattr(char *name)
{
	acl_t		acl;
	acl_entry_t	entry;
	ssize_t		xattr;

	acl = acl_get_link_np(name, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &entry) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(name, NULL, 0, XATTR_NOFOLLOW);
	if (xattr > 0)
		return ('@');
	else if (acl != NULL)
	{
		acl_free(acl);
		acl = NULL;
		return ('+');
	}
	else
		return (' ');
}

static void	ft_print_long_aux(t_show *sh, t_ftree *ft, struct stat *st,
																	char *buf)
{
	ft_printf("%s %*u %-*s  %-*s  ", buf, sh->s_nlink, st->st_nlink,
						sh->s_user, ft->ugf->user, sh->s_group, ft->ugf->group);
	if (g_lsf & F_FLAGS)
		ft_printf("%-*s ", sh->s_flags, ft->ugf->flags);
	if (S_ISCHR(st->st_mode) || S_ISBLK(st->st_mode))
		ft_printf("%3d, %3d ", major(st->st_rdev), minor(st->st_rdev));
	else if (sh->bcfile)
		ft_printf("%*s%*lld ", 8 - sh->s_size, "", sh->s_size, st->st_size);
	else
		ft_printf("%*lld ", sh->s_size, st->st_size);
	if (g_lsf & F_ACCESSTM)
		ft_print_time(st->st_atime, 4);
	else if (g_lsf & F_STATTIME)
		ft_print_time(st->st_ctime, 4);
	else
		ft_print_time(st->st_mtime, 4);
	if (g_lsf & F_COLOR)
		ft_colorize(st->st_mode);
	ft_printf("%s" NONE, ft->name);
	if (g_lsf & F_TYPE)
		ft_print_type(st->st_mode);
	if (S_ISLNK(st->st_mode))
		ft_print_link(ft);
	ft_printf("\n");
}

void		ft_print_long(t_show *sh)
{
	t_ftree		*ft;
	char		buf[20];

	ft = sh->ft;
	if (sh->dir && sh->entries)
		ft_print_total(sh->btotal);
	while (ft)
	{
		if (ft->notshow || ft->err)
		{
			ft = ft->next;
			continue;
		}
		ft_strmode(ft->st->st_mode, buf);
		buf[10] = ft_acl_xattr(ft->fullname);
		if (g_lsf & F_INODE)
			ft_printf("%*llu ", sh->s_inode, ft->st->st_ino);
		if (g_lsf & F_SIZE)
			ft_printf("%*lld ", sh->s_block,
								(ft->st->st_blocks + g_blk_sz - 1) / g_blk_sz);
		ft_print_long_aux(sh, ft, ft->st, buf);
		ft = ft->next;
	}
	ft_print_err(sh->ft);
}
