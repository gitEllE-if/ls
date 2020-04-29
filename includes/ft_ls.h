#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "ft_getopt.h"
# include "ft_hash.h"
# include <dirent.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/syslimits.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <string.h>

/*
** 1ClRrftiscuAadmOqFTLPSUG
*/
# define F_SINGLECOL	1
# define F_COLUMN		2
# define F_LONGFORM		4
# define F_RECURSIVE	8
# define F_REVSORT		16
# define F_NOSORT		32
# define F_TIMESORT		64
# define F_INODE		128
# define F_SIZE			256
# define F_STATTIME		512
# define F_ACCESSTM		1024
# define F_LISTDOT		2048
# define F_SEEDOT		4096
# define F_LISTDIR		8192
# define F_STRING		16384
# define F_FLAGS		32768
# define F_NONPRINT		65536
# define F_TYPE			131072
# define F_SECTIME		262144
# define F_GOLINK		524288
# define F_PLINK		1048576
# define F_SIZESORT		2097152
# define F_BIRTHTM		4194304
# define F_COLOR		8388608

# define MAX(a, b)		a > b ? a : b

typedef struct		s_prn
{
	int32_t			col;
	int32_t			row;
	int32_t			col_cnt;
	int32_t			row_cnt;
	int32_t			col_end;
	int32_t			cnt;
}					t_prn;

typedef struct		s_name
{
	char			*user;
	char			*group;
	char			*flags;
	char			data[1];
}					t_name;

typedef struct		s_ftree
{
	char			fullname[PATH_MAX];
	char			name[NAME_MAX];
	uint64_t		parent;
	uint32_t		lev;
	int32_t			err;
	int8_t			dot;
	int8_t			hidn;
	int8_t			notshow;
	int8_t			root;
	struct stat		*st;
	struct s_name	*ugf;
	struct s_ftree	*next;
	struct s_ftree	*down;
	struct s_ftree	*last;
}					t_ftree;

typedef struct		s_show
{
	t_ftree			*ft;
	uint64_t		btotal;
	uint64_t		stotal;
	int32_t			s_block;
	int32_t			s_flags;
	int32_t			s_group;
	int32_t			s_inode;
	int32_t			s_nlink;
	int32_t			s_size;
	int32_t			s_user;
	int32_t			bcfile;
	int32_t			entries;
	int32_t			maxlen;
	int8_t			dir;
}					t_show;

typedef	int32_t		(*t_cmpfun)(t_ftree *, t_ftree *);
typedef void		(*t_prnfun)(t_show *);

extern uint32_t		g_lsf;
extern t_cmpfun		g_cmpfun;
extern t_prnfun		g_prnfun;
extern long			g_blk_sz;
extern int32_t		g_term_wd;

int32_t				ft_ls(t_ftree **er_l, t_ftree **file_l, t_ftree **dir_l);
void				ft_usage(void);
void				ft_ftwalk(char *pathname, t_ftree **ft);
void				ft_recursive_walk(struct dirent *d, uint32_t lev,
																uint64_t hash);
void				ft_strmode(int32_t mode, char *str);
void				ft_get_term(void);
void				ft_nonprint_override(char *s, char *d, int32_t len);
char				*ft_flag_to_str(uint64_t flags, char *deflt);
void				ft_show(t_ftree *ft, int8_t dir, uint64_t hash);
void				ft_recursive_view(t_ftree *ft, t_ftree *elem, uint64_t h);
void				ft_print_1col(t_show *show);
void				ft_print_long(t_show *show);
void				ft_print_col(t_show *show);
void				ft_print_stream(t_show *show);
void				ft_print_err(t_ftree *err_list);
int32_t				ft_print_type(int32_t mode);
int32_t				ft_print_name(t_ftree *ft, int32_t inode, int32_t size);
void				ft_colorize(int32_t mode);
void				ft_parse_opt(int argc, char **argv);
void				ft_set_sortfun(void);
void				ft_set_printfun(void);
void				ft_print_total(uint64_t block_total);
void				ft_print_dirname(t_ftree *elem);
void				ft_user_group_flag(t_ftree *elem, t_show *show);

int32_t				namecmp(t_ftree *a, t_ftree *b);
int32_t				revnamecmp(t_ftree *a, t_ftree *b);
int32_t				mtimecmp(t_ftree *a, t_ftree *b);
int32_t				revmtimecmp(t_ftree *a, t_ftree *b);
int32_t				atimecmp(t_ftree *a, t_ftree *b);
int32_t				revatimecmp(t_ftree *a, t_ftree *b);
int32_t				ctimecmp(t_ftree *a, t_ftree *b);
int32_t				revctimecmp(t_ftree *a, t_ftree *b);
int32_t				btimecmp(t_ftree *a, t_ftree *b);
int32_t				revbtimecmp(t_ftree *a, t_ftree *b);
int32_t				sizecmp(t_ftree *a, t_ftree *b);
int32_t				revsizecmp(t_ftree *a, t_ftree *b);

t_ftree				*ft_ftree_new_elem(char *fullname, uint32_t lev,
											struct dirent *dirp, uint64_t hash);
t_ftree				*ft_ftree_fill(char *fullname, struct dirent *dirp,
												uint32_t lev, uint64_t hash);
void				ft_ftree_free(t_ftree **ft, int8_t dir);
void				ft_ftree_sort(t_ftree **ft, t_ftree *down,
									int32_t (*ft_cmp)(t_ftree *, t_ftree *));
void				ft_ftree_downsort(t_ftree **ft,
										int32_t (*cmp)(t_ftree *, t_ftree *));
void				ft_ftree_push_back(t_ftree **ft, t_ftree *node);

#endif
