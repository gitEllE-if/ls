#include "ft_ls.h"

void					ft_print_1col(t_show *sh)
{
	t_ftree *ft;

	ft = sh->ft;
	while (ft)
	{
		if (ft->notshow || ft->err)
		{
			ft = ft->next;
			continue;
		}
		ft_print_name(ft, sh->s_inode, sh->s_block);
		ft_printf("\n");
		ft = ft->next;
	}
	ft_print_err(sh->ft);
}

static void				ft_print_col_aux(t_show *sh, t_ftree **ft_arr,
												t_prn *prn, int32_t col_width)
{
	int32_t	c_cnt;
	int32_t	c;
	int32_t	pos;

	prn->row = -1;
	while (++prn->row < prn->row_cnt)
	{
		prn->col_end = col_width;
		pos = prn->row;
		c_cnt = 0;
		prn->col = -1;
		while (++prn->col < prn->col_cnt)
		{
			c_cnt += ft_print_name(ft_arr[pos], sh->s_inode, sh->s_block);
			if ((pos += prn->row_cnt) >= prn->cnt)
				break ;
			while ((c = (c_cnt + 8 & ~(8 - 1))) <= prn->col_end)
			{
				ft_printf("\t");
				c_cnt = c;
			}
			prn->col_end += col_width;
		}
		ft_printf("\n");
	}
}

static inline int32_t	ft_col_width(t_show *sh)
{
	int32_t	col_width;

	col_width = sh->maxlen;
	if (g_lsf & F_INODE)
		col_width += sh->s_inode + 1;
	if (g_lsf & F_TYPE)
		col_width += 1;
	if (g_lsf & F_SIZE)
		col_width += sh->s_block + 1;
	col_width = (col_width + 8) & ~(8 - 1);
	if (g_term_wd < 2 * col_width)
	{
		ft_print_1col(sh);
		return (-1);
	}
	return (col_width);
}

void					ft_print_col(t_show *sh)
{
	t_ftree	*ft_arr[5000];
	t_ftree	*ft;
	t_prn	prn;
	int32_t	col_width;

	ft = sh->ft;
	if (!ft)
		return ;
	prn.cnt = 0;
	while (ft && prn.cnt < 5000)
	{
		if (!ft->notshow && !ft->err)
			ft_arr[prn.cnt++] = ft;
		ft = ft->next;
	}
	if ((col_width = ft_col_width(sh)) == -1)
		return ;
	prn.col_cnt = g_term_wd / col_width;
	prn.row_cnt = prn.cnt / prn.col_cnt;
	if (prn.cnt % prn.col_cnt)
		++prn.row_cnt;
	if (sh->dir && sh->entries && (g_lsf & F_SIZE))
		ft_print_total(sh->btotal);
	ft_print_col_aux(sh, ft_arr, &prn, col_width);
	ft_print_err(sh->ft);
}
