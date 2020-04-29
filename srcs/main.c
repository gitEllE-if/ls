#include "ft_ls.h"

uint32_t	g_lsf = 0;
t_cmpfun	g_cmpfun = 0;
int32_t		g_term_wd = 80;

void	ft_make_list(t_ftree **err_list, t_ftree **file_list,
											t_ftree **dir_list, t_ftree **ft)
{
	if ((*ft)->err && (*ft)->err != 13)
		ft_ftree_push_back(err_list, *ft);
	else
	{
		if (!(g_lsf & F_NOSORT))
			ft_ftree_downsort(ft, g_cmpfun);
		if (S_ISDIR((*ft)->st->st_mode) && !(g_lsf & F_LISTDIR))
			ft_ftree_push_back(dir_list, *ft);
		else
			ft_ftree_push_back(file_list, *ft);
	}
}

void	ft_init_g_var(int argc, char **argv)
{
	ft_parse_opt(argc, argv);
	ft_get_term();
	ft_set_sortfun();
	ft_set_printfun();
}

int		main(int argc, char **argv)
{
	t_ftree		*file_list = NULL;
	t_ftree		*dir_list = NULL;
	t_ftree		*err_list = NULL;
	t_ftree		*ft;
	int32_t		i;

	i = -1;
	ft_init_g_var(argc, argv);
	if ((argc -= g_optind) == 0)
	{
		ft_ftwalk(".", &dir_list);
		if (!(g_lsf & F_NOSORT))
			ft_ftree_downsort(&dir_list, g_cmpfun);
	}
	else
	{
		while (++i < argc)
		{
			ft = NULL;
			ft_ftwalk(argv[i + g_optind], &ft);
			ft_make_list(&err_list, &file_list, &dir_list, &ft);
		}
	}
	return (ft_ls(&err_list, &file_list, &dir_list));
}

void	ft_recursive_view(t_ftree *ft, t_ftree *elem, uint64_t hash)
{
	if (!ft || elem->dot || (elem->hidn && !(g_lsf & (F_SEEDOT | F_LISTDOT))))
		return ;
	if (!elem->root)
	{
		ft_printf("\n");
		ft_print_dirname(elem);
	}
	if (elem->err)
	{
		ft_printf("%s: %s: %s\n", g_app_name, elem->name, strerror(elem->err));
		return ;
	}
	ft_show(ft->down, 1, hash);
	if (!(g_lsf & F_RECURSIVE))
		return ;
	ft = ft->down;
	elem = ft;
	while (elem)
	{
		if (S_ISDIR(elem->st->st_mode) && (elem->parent == hash))
			ft_recursive_view(ft, elem, ft_hash(elem->fullname));
		elem = elem->next;
	}
}
