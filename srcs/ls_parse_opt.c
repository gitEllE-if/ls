#include "ft_ls.h"

static void			ft_override_opt(int32_t opt)
{
	if (opt == '1')
		g_lsf &= ~(F_LONGFORM | F_COLUMN | F_STRING);
	else if (opt == 'l')
		g_lsf &= ~(F_SINGLECOL | F_COLUMN | F_STRING);
	else if (opt == 'C')
		g_lsf &= ~(F_SINGLECOL | F_LONGFORM | F_STRING);
	else if (opt == 'm')
		g_lsf &= ~(F_SINGLECOL | F_COLUMN | F_LONGFORM);
	else if (opt == 'd')
		g_lsf &= ~F_RECURSIVE;
	else if (opt == 'c')
		g_lsf &= ~(F_ACCESSTM | F_BIRTHTM);
	else if (opt == 'u')
		g_lsf &= ~(F_STATTIME | F_BIRTHTM);
	else if (opt == 'U')
		g_lsf &= ~(F_ACCESSTM | F_STATTIME);
	else if (opt == 'L')
		g_lsf &= ~F_PLINK;
	else if (opt == 'P')
		g_lsf &= ~F_GOLINK;
	else if (opt == 'f')
		g_lsf |= F_SEEDOT;
}

void				ft_parse_opt(int argc, char **argv)
{
	int32_t			c;
	const char		*opt;
	const char		opt_str[] = "1ClRrftiscuAadmOqFTLPSUG";
	const uint32_t	opt_bit[] = {F_SINGLECOL, F_COLUMN, F_LONGFORM, F_RECURSIVE,
					F_REVSORT, F_NOSORT, F_TIMESORT, F_INODE, F_SIZE,
					F_STATTIME, F_ACCESSTM, F_LISTDOT, F_SEEDOT, F_LISTDIR,
					F_STRING, F_FLAGS, F_NONPRINT, F_TYPE, F_SECTIME,
					F_GOLINK, F_PLINK, F_SIZESORT, F_BIRTHTM, F_COLOR, 0};

	while ((c = ft_getopt(argc, argv, opt_str)) != -1)
	{
		if (c == '?')
			ft_usage();
		opt = ft_strchr(opt_str, c);
		g_lsf |= opt_bit[opt - opt_str];
		ft_override_opt(c);
	}
}

static inline void	ft_set_revsortfun(void)
{
	if (g_lsf & F_SIZESORT)
		g_cmpfun = revsizecmp;
	else if (!(g_lsf & F_TIMESORT))
		g_cmpfun = revnamecmp;
	else if (g_lsf & F_ACCESSTM)
		g_cmpfun = revatimecmp;
	else if (g_lsf & F_STATTIME)
		g_cmpfun = revctimecmp;
	else if (g_lsf & F_BIRTHTM)
		g_cmpfun = revbtimecmp;
	else
		g_cmpfun = revmtimecmp;
}

void				ft_set_sortfun(void)
{
	if (g_lsf & F_REVSORT)
		ft_set_revsortfun();
	else
	{
		if (g_lsf & F_SIZESORT)
			g_cmpfun = sizecmp;
		else if (!(g_lsf & F_TIMESORT))
			g_cmpfun = namecmp;
		else if (g_lsf & F_ACCESSTM)
			g_cmpfun = atimecmp;
		else if (g_lsf & F_STATTIME)
			g_cmpfun = ctimecmp;
		else if (g_lsf & F_BIRTHTM)
			g_cmpfun = btimecmp;
		else
			g_cmpfun = mtimecmp;
	}
}

void				ft_set_printfun(void)
{
	if (g_lsf & F_SINGLECOL)
		g_prnfun = ft_print_1col;
	else if (g_lsf & F_LONGFORM)
		g_prnfun = ft_print_long;
	else if (g_lsf & F_STRING)
		g_prnfun = ft_print_stream;
	else
		g_prnfun = ft_print_col;
}
