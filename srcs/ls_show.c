#include "ft_ls.h"

t_prnfun g_prnfun;

static inline void		ft_show_init(t_show *show, t_ftree *ft, int8_t dir,
															uint64_t *max_islb)
{
	show->ft = ft;
	show->btotal = 0;
	show->stotal = 0;
	show->maxlen = 0;
	show->entries = 0;
	show->bcfile = 0;
	show->s_block = 0;
	show->s_flags = 0;
	show->s_group = 0;
	show->s_inode = 0;
	show->s_nlink = 0;
	show->s_size = 0;
	show->s_user = 0;
	show->dir = dir;
	max_islb[0] = 0;
	max_islb[1] = 0;
	max_islb[2] = 0;
	max_islb[3] = 0;
}

static inline int8_t	ft_not_show(t_ftree *elem, uint64_t hash)
{
	if (elem->dot && !(g_lsf & F_SEEDOT))
	{
		elem->notshow = 1;
		return (1);
	}
	if (elem->hidn && !(g_lsf & (F_LISTDOT | F_SEEDOT)))
	{
		elem->notshow = 1;
		return (1);
	}
	if (g_lsf & F_RECURSIVE)
	{
		if (elem->parent != hash)
		{
			elem->notshow = 1;
			return (1);
		}
		else
			elem->notshow = 0;
	}
	return (0);
}

static inline void		ft_get_maxislb(t_ftree *elem, t_show *show,
															uint64_t *max_islb)
{
	max_islb[0] = MAX(elem->st->st_ino, max_islb[0]);
	max_islb[1] = MAX(elem->st->st_size, (int64_t)max_islb[1]);
	max_islb[2] = MAX(elem->st->st_nlink, max_islb[2]);
	max_islb[3] = MAX(elem->st->st_blocks, (int64_t)max_islb[3]);
	show->btotal += elem->st->st_blocks;
	show->stotal += elem->st->st_size;
	if (g_lsf & F_LONGFORM)
	{
		if (S_ISCHR(elem->st->st_mode) || S_ISBLK(elem->st->st_mode))
			show->bcfile = 1;
		ft_user_group_flag(elem, show);
	}
	++show->entries;
}

static inline void		ft_set_maxislb(t_show *show, uint64_t *max_islb)
{
	char	buf[20];

	ft_sprintf(buf, "%llu", max_islb[0]);
	show->s_inode = ft_strlen(buf);
	ft_sprintf(buf, "%llu", max_islb[1]);
	show->s_size = ft_strlen(buf);
	ft_sprintf(buf, "%llu", max_islb[2]);
	show->s_nlink = ft_strlen(buf);
	ft_sprintf(buf, "%llu", (max_islb[3] + g_blk_sz - 1) / g_blk_sz);
	show->s_block = ft_strlen(buf);
}

void					ft_show(t_ftree *ft, int8_t dir, uint64_t hash)
{
	t_show		show;
	int32_t		len;
	uint64_t	max_islb[4];

	if (!ft)
		return ;
	ft_show_init(&show, ft, dir, max_islb);
	while (ft)
	{
		if (dir && ft_not_show(ft, hash))
		{
			ft = ft->next;
			continue;
		}
		len = ft_strlen(ft->name);
		if (g_lsf & F_NONPRINT)
			ft_nonprint_override(ft->name, ft->name, len);
		show.maxlen = MAX(len, show.maxlen);
		if (g_lsf & (F_INODE | F_LONGFORM | F_SIZE))
			ft_get_maxislb(ft, &show, max_islb);
		ft = ft->next;
	}
	if (g_lsf & (F_INODE | F_LONGFORM | F_SIZE))
		ft_set_maxislb(&show, max_islb);
	g_prnfun(&show);
}
