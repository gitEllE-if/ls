#include "ft_ls.h"
#include "ft_hash.h"

long		g_blk_sz;

void		ft_usage(void)
{
	ft_fprintf(2,
			"usage: ft_ls [-ACFGLOPRSTUacdfilmqrstu1] [file ...]\n");
	exit(1);
}

void		ft_get_term(void)
{
	struct winsize	win;
	int32_t			notused;
	char			*s;

	if (isatty(STDOUT_FILENO))
	{
		if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &win) == -1 || !win.ws_col)
		{
			if ((s = getenv("COLUMNS")) != NULL)
				g_term_wd = ft_atoi(s);
		}
		else
			g_term_wd = win.ws_col;
		g_lsf |= F_COLUMN;
	}
	else
		g_lsf |= F_SINGLECOL;
	if (g_lsf & (F_LONGFORM | F_SIZE | F_INODE))
	{
		getbsize(&notused, &g_blk_sz);
		g_blk_sz /= 512;
	}
}

void		ft_nonprint_override(char *src, char *dest, int32_t len)
{
	int32_t	c;

	while (len--)
	{
		c = *src++;
		*dest++ = ft_isprint(c) ? c : '?';
	}
}

uint64_t	ft_hash(char *str)
{
	uint64_t	hash;
	uint32_t	i;

	i = 0;
	hash = 0;
	while (str[i])
	{
		hash += (str[i] - 'a' + 1) * g_hash_pow[i % 1024];
		i++;
	}
	return (hash);
}
