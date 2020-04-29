#include "ft_ls.h"

static inline char	*ft_flag1(t_ftree *elem, t_show *show, int32_t *ugf)
{
	char	*flags;

	flags = ft_flag_to_str(elem->st->st_flags, "-");
	ugf[2] = ft_strlen(flags);
	show->s_flags = MAX(ugf[2], show->s_flags);
	return (flags);
}

static inline void	ft_flag2(t_name *nm, int32_t *ugf, char *flags)
{
	nm->flags = &nm->data[ugf[0] + ugf[1] + 2];
	ft_strcpy(nm->flags, flags);
}

void				ft_user_group_flag(t_ftree *elem, t_show *show)
{
	char		*user;
	char		*group;
	char		*flags;
	int32_t		ugf[3];
	t_name		*nm;

	user = user_from_uid(elem->st->st_uid, 0);
	group = group_from_gid(elem->st->st_gid, 0);
	ugf[0] = ft_strlen(user);
	show->s_user = MAX(ugf[0], show->s_user);
	ugf[1] = ft_strlen(group);
	show->s_group = MAX(ugf[1], show->s_group);
	if (g_lsf & F_FLAGS)
		flags = ft_flag1(elem, show, ugf);
	else
		ugf[2] = 0;
	if ((nm = malloc(sizeof(t_name) + ugf[0] + ugf[1] + ugf[2])) == NULL)
		exit(1);
	nm->user = &nm->data[0];
	ft_strcpy(nm->user, user);
	nm->group = &nm->data[ugf[0] + 1];
	ft_strcpy(nm->group, group);
	if (g_lsf & F_FLAGS)
		ft_flag2(nm, ugf, flags);
	elem->ugf = nm;
}
