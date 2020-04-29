#include "ft_ls.h"

void	ft_ls_err_list(t_ftree **err_list, int32_t *dir_name)
{
	(*dir_name)++;
	ft_ftree_sort(err_list, NULL, namecmp);
	ft_print_err(*err_list);
	ft_ftree_free(err_list, 0);
}

void	ft_ls_file_list(t_ftree **file_list, t_ftree *dir_list,
															int32_t *dir_name)
{
	(*dir_name)++;
	if (!(g_lsf & F_NOSORT))
		ft_ftree_sort(file_list, NULL, g_cmpfun);
	ft_show(*file_list, 0, 0);
	ft_ftree_free(file_list, 0);
	if (dir_list)
		ft_printf("\n");
}

void	ft_ls_dir_list(t_ftree **dir_list, int32_t dir_name)
{
	t_ftree *elem;
	t_ftree	*elem1;

	if ((*dir_list)->next)
		dir_name++;
	if (!(g_lsf & F_NOSORT))
		ft_ftree_sort(dir_list, NULL, g_cmpfun);
	if (dir_name)
		ft_print_dirname(*dir_list);
	(*dir_list)->root = 1;
	elem = *dir_list;
	while (elem)
	{
		ft_recursive_view(elem, elem, ft_hash(elem->fullname));
		elem = elem->next;
	}
	elem = *dir_list;
	while (elem)
	{
		elem1 = elem->next;
		ft_ftree_free(&elem, 1);
		elem = elem1;
	}
}

int		ft_ls(t_ftree **err_list, t_ftree **file_list, t_ftree **dir_list)
{
	int32_t	dir_name;

	dir_name = 0;
	if (*err_list)
		ft_ls_err_list(err_list, &dir_name);
	if (*file_list)
		ft_ls_file_list(file_list, *dir_list, &dir_name);
	if (*dir_list)
		ft_ls_dir_list(dir_list, dir_name);
	return (0);
}
