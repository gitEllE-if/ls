#include "ft_ls.h"

int32_t				ft_print_type(int32_t mode)
{
	if (S_ISDIR(mode))
		ft_printf("/");
	else if (S_ISFIFO(mode))
		ft_printf("|");
	else if (S_ISLNK(mode))
		ft_printf("@");
	else if (S_ISSOCK(mode))
		ft_printf("=");
	else if (S_ISWHT(mode))
		ft_printf("%%");
	else if (mode & (S_IXUSR | S_IXGRP | S_IXOTH))
		ft_printf("*");
	else
		return (0);
	return (1);
}

int32_t				ft_print_name(t_ftree *ft, int32_t inode_wid,
															int32_t size_wid)
{
	int			c_cnt;
	struct stat	*st;

	st = ft->st;
	c_cnt = 0;
	if (g_lsf & F_INODE)
		c_cnt += ft_printf("%*llu ", inode_wid, st->st_ino);
	if (g_lsf & F_SIZE)
		c_cnt += ft_printf("%*lld ", size_wid,
									(st->st_blocks + g_blk_sz - 1) / g_blk_sz);
	if (g_lsf & F_COLOR)
		ft_colorize(st->st_mode);
	c_cnt += ft_printf("%s", ft->name);
	if (g_lsf & F_COLOR)
		ft_printf(NONE);
	if (g_lsf & F_TYPE)
		c_cnt += ft_print_type(st->st_mode);
	return (c_cnt);
}

void				ft_print_stream(t_show *sh)
{
	t_ftree		*ft;
	int32_t		c;

	ft = sh->ft;
	c = 0;
	while (ft)
	{
		if (ft->notshow || ft->err)
		{
			ft = ft->next;
			continue;
		}
		if (ft_strlen(ft->name) + c + (ft->next ? 2 : 0) >= (uint32_t)g_term_wd)
		{
			ft_printf("\n");
			c = 0;
		}
		c += ft_print_name(ft, sh->s_inode, sh->s_block);
		if (ft->next)
			c += ft_printf(", ");
		ft = ft->next;
	}
	if (c)
		ft_printf("\n");
	ft_print_err(ft);
}
