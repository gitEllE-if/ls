#include "ft_ls.h"

void	ft_colorize(int32_t mode)
{
	if (S_ISDIR(mode))
	{
		ft_printf(BOLD);
		ft_printf(F_BLUE);
	}
	else if (S_ISCHR(mode))
		ft_printf(F_GREEN);
	else if (S_ISBLK(mode))
		ft_printf(F_CYAN);
	else if (S_ISLNK(mode))
		ft_printf(F_MAGENTA);
	else if (mode & (S_IXUSR | S_IXGRP | S_IXOTH))
	{
		ft_printf(BOLD);
		ft_printf(ITALIC);
		ft_printf(F_RED);
	}
	else if (S_ISSOCK(mode))
		ft_printf(ITALIC);
	else if (S_ISFIFO(mode))
		ft_printf(ITALIC);
}

void	ft_print_total(uint64_t blk_total)
{
	if (g_lsf & F_COLOR)
	{
		ft_printf(BOLD);
		ft_printf(UNDERLINE);
		ft_printf(ITALIC);
		ft_printf(F_CYAN);
	}
	ft_printf("total %llu\n" NONE, (blk_total + g_blk_sz - 1) / g_blk_sz);
}

void	ft_print_dirname(t_ftree *elem)
{
	if (g_lsf & F_COLOR)
	{
		ft_printf(B_BLUE);
		ft_printf(F_WHITE);
		ft_printf(BOLD);
		ft_printf(ITALIC);
	}
	ft_printf("%s:" NONE "\n", elem->fullname);
}

void	ft_print_err(t_ftree *err_list)
{
	t_ftree	*elem;

	elem = err_list;
	while (elem)
	{
		if (elem->err && !elem->notshow && elem->lev != 1)
			ft_printf("%s: %s: %s\n", g_app_name, elem->fullname,
														strerror(elem->err));
		elem = elem->next;
	}
}
